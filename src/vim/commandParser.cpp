#include "commandParser.hpp"

#include <ncurses.h>

#include "../storage/storage.hpp"
#include "../stringUtils.hpp"
#include "mode.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {

CommandParser::CommandParser(VimState* state)
    : mState(state) {}

ParserResult CommandParser::handleKey(Mode& outMode) {
	int ch = getch();
	if (ch == ERR) return Res::NOPE;

	switch (ch) {
	case 27: {  // ESC
		mHistoryIndex = 0;
		mCommand = "";
		outMode = Mode::NORMAL;
		return Res::UPDATE;
	}
	case KEY_ENTER:
	case '\n': {  // ENTER
		mHistory.emplace_back(mCommand);
		mHistoryIndex = 0;

		Res res = handleCommand(outMode);
		if (res != Res::ERROR && res != Res::UNKNOWN) {
			// mCommand = "";
			outMode = Mode::NORMAL;
		}
		mCommand = "";
		return res;
	}
	case KEY_BACKSPACE: {
		if (!mCommand.empty())
			mCommand.erase(--mCommand.end());
		return Res::UPDATE;
	}
	case KEY_UP: {
		browseHistory(true);
		return Res::UPDATE;
	}
	case KEY_DOWN: {
		browseHistory(false);
		return Res::UPDATE;
	}
	}
	if (' ' <= ch && ch <= '~') {
		mCommand += ch;
		return Res::UPDATE;
	}
	return Res::NOPE;
}

void CommandParser::browseHistory(const bool inc) {
	if (!inc && mHistoryIndex == 0) {
		mCommand = "";
		mLatest = "";
		return;
	}

	if (mHistoryIndex == 0) mLatest = mCommand;

	if (inc && mHistoryIndex != mHistory.size()) {
		++mHistoryIndex;
	} else if (!inc) {
		--mHistoryIndex;
	}

	if (mHistoryIndex == 0) mCommand = mLatest;
	else mCommand = mHistory[mHistory.size() - mHistoryIndex];
}

ParserResult CommandParser::handleCommand(Mode& outMode) {
	trim(mCommand);
	if (mCommand.empty()) return ParserResult::UPDATE;

	ParserResult res;

	res = tryQuitAndWrite(outMode);
	if (res != ParserResult::UNKNOWN) return res;

	res = tryOpenFile(outMode);
	if (res != ParserResult::UNKNOWN) return res;

	res = tryExportFile(outMode);
	if (res != ParserResult::UNKNOWN) return res;

	res = tryJump(outMode);
	if (res != ParserResult::UNKNOWN) return res;

	return mState->setError("Unknown command "s + mCommand, Mode::COMMAND, outMode);
}

ParserResult CommandParser::tryQuitAndWrite(Mode& outMode) {
	if (mCommand == "q") {
		if (mState->mTable->changed() && !mState->mTable->isEmpty())
			return mState->setError("You have unsaved changes", Mode::COMMAND, outMode);
		else
			return ParserResult::QUIT;
	}

	if (mCommand == "q!") return ParserResult::QUIT;

	if (mCommand == "wq" || mCommand == "w") {
		if (mState->mFilename.empty())
			return mState->setError("No filename specified", Mode::COMMAND, outMode);

		try {
			storage::Storage::saveData(mState->mTable, mState->mFilename);
		} catch (exception& e) {
			return mState->setError("Failed to save file: "s + e.what(), Mode::COMMAND, outMode);
		}
		mState->mTable->clearChanged();

		if (mCommand == "w")
			return ParserResult::UPDATE;
		else
			return ParserResult::QUIT;
	}

	const auto save = [&](size_t len) -> bool {
		string filename = string(mCommand.begin() + len, mCommand.end());
		trim(filename);
		if (filename.empty()) {
			mState->mErrorMsg = "No filename entered";
			return false;
		}
		if (mState->mFilename == "") mState->mFilename = filename;
		storage::Storage::saveData(mState->mTable, filename);
		mState->mTable->clearChanged();
		return true;
	};

	try {
		if (mCommand.rfind("w ", 0) == 0)
			return save(2) ? ParserResult::UPDATE : mState->setError("No filename specified", Mode::COMMAND, outMode);
		if (mCommand.rfind("wq ") == 0)
			return save(3) ? ParserResult::QUIT : mState->setError("No filename specified", Mode::COMMAND, outMode);
	} catch (exception& e) {
		return mState->setError("Failed to save file: "s + e.what(), Mode::COMMAND, outMode);
	}
	return ParserResult::UNKNOWN;
}

Res CommandParser::tryOpenFile(Mode& outMode) {
	if (mCommand.rfind("o ") == 0 || mCommand.rfind("o! ") == 0) {
		const bool force = mCommand[1] == '!';
		const string filename = string(mCommand.begin() + (!force ? 2 : 3), mCommand.end());

		if (filename.empty())
			return mState->setError("You have to enter a valid filename, no empty string", Mode::COMMAND, outMode);

		if (!force && (mState->mTable->changed() && !mState->mTable->isEmpty()))
			return mState->setError("You have unsaved changes", Mode::COMMAND, outMode);

		mState->mTable->deleteAll();
		try {
			storage::Storage::loadData(mState->mTable, filename);
			mState->mTable->clearChanged();
			mState->mFilename = filename;
			return Res::UPDATE;
		} catch (exception& e) {
			return mState->setError("Failed to loadfile: "s + e.what(), Mode::COMMAND, outMode);
		}
	}
	return Res::UNKNOWN;
}

Res CommandParser::tryExportFile(Mode& outMode) {
	if (mCommand.rfind("exp ") == 0) {
		const string filename = string(mCommand.begin() + 4, mCommand.end());

		if (filename.empty())
			return mState->setError("You have to enter a valid filename, no empty string", Mode::COMMAND, outMode);

		try {
			storage::Storage::exportData(mState->mTable, filename);
			return Res::UPDATE;
		} catch (exception& e) {
			return mState->setError("Failed to loadfile: "s + e.what(), Mode::COMMAND, outMode);
		}
	}
	return Res::UNKNOWN;
}

ParserResult CommandParser::tryJump(Mode&) {
	string letters;
	size_t pos = 0;
	bool inDigits = false;
	for (auto itr = mCommand.begin(); itr != mCommand.end(); ++itr) {
		char c = *itr;
		if (isdigit(c)) {
			inDigits = true;
			pos *= 10;
			pos += c - '0';
		} else if (isalpha(c)) {
			if (inDigits) break;
			letters += c;
		} else
			break;
	}
	if (!letters.empty() && pos > 0) {
		mState->mDisplayState->setPosition(table::Coordinates(letters, pos));
		return ParserResult::UPDATE;
	}
	return ParserResult::UNKNOWN;
}

pair<string, size_t> CommandParser::getTextAndPosition() {
	return make_pair(":"s + mCommand, (size_t)-1);
}
}  // namespace cz::lastaapps::vimxel::vim
