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
		mCommand = "";
		outMode = Mode::NORMAL;
		return Res::UPDATE;
	}
	case KEY_ENTER:
	case '\n': {  // ENTER
		Res res = handleCommand(outMode);
		if (res != Res::UNKNOWN) {
			mCommand = "";
			outMode = Mode::NORMAL;
		} else if (mCommand == "")
			outMode = Mode::NORMAL;

		return res;
	}
	case KEY_BACKSPACE: {
		if (!mCommand.empty())
			mCommand.erase(--mCommand.end());
		return Res::UPDATE;
	}
	}
	if (' ' <= ch && ch <= '~') {
		mCommand += ch;
		return Res::UPDATE;
	}
	return Res::NOPE;
}

ParserResult CommandParser::handleCommand(Mode& outMode) {
	trim(mCommand);
	if (mCommand.empty()) return ParserResult::NOPE;

	{
		auto res = tryQuitAndWrite(outMode);
		if (res != ParserResult::UNKNOWN) return res;
	}
	{
		auto res = tryJump(outMode);
		if (res != ParserResult::UNKNOWN) return res;
	}
	return ParserResult::UNKNOWN;
}
ParserResult CommandParser::tryQuitAndWrite(Mode& outMode) {
	if (mCommand == "q") {
		if (mState->mTable->changed()) {
			mState->mErrorMsg = "You have unsaved changes";
			mState->mReturnMode = Mode::COMMAND;
			outMode = Mode::ERROR;
			return ParserResult::UPDATE;
		} else {
			return ParserResult::QUIT;
		}
	}
	if (mCommand == "q!") return ParserResult::QUIT;
	if (mCommand == "wq" || mCommand == "w") {
		if (mState->mFilename.empty()){
			mState->mErrorMsg = "No filename specified";
			mState->mReturnMode = Mode::COMMAND;
			outMode = Mode::ERROR;
			return ParserResult::UPDATE;
		}
		storage::Storage::saveData(mState->mTable, mState->mFilename);
		mState->mTable->clearChanged();
		if (mCommand == "w")
			return ParserResult::UPDATE;
		else
			return ParserResult::QUIT;
	}
	auto save = [&](size_t len) -> bool {
		string filename = string(mCommand.begin() + len, mCommand.end());
		trim(filename);
		if (filename.empty()) {
			mState -> mErrorMsg = "No filename entered";
			return false;
		}
		if (mState->mFilename == "") mState->mFilename = filename;
		storage::Storage::saveData(mState->mTable, filename);
		return true;
	};

	mState->mErrorMsg = "No filename specified";
	mState->mReturnMode = Mode::COMMAND;
	if (mCommand.rfind("w ", 0) == 0) {
		return save(2) ? ParserResult::UPDATE : (outMode = Mode::ERROR, ParserResult::UPDATE);
	}
	if (mCommand.rfind("wq ") == 0) {
		return save(3) ? ParserResult::QUIT : (outMode = Mode::ERROR, ParserResult::UPDATE);
	}
	return ParserResult::UNKNOWN;
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
