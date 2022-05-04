#include "commandParser.hpp"

#include <ncurses.h>

#include "mode.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {

CommandParser::CommandParser(VimState* state)
    : mState(state) {}

ParserResult CommandParser::handleKey(Mode& outMode) {
	using Res = ParserResult;
	int ch = getch();
	if (ch == ERR) return Res::NOPE;

	switch (ch) {
	case 27: { // ESC
		mCommand = "";
		outMode = Mode::NORMAL;
		return Res::FINE;
	}
    case KEY_ENTER:
	case '\n': { // ENTER
		Res res = handleCommand();
		mCommand = "";
		outMode = Mode::NORMAL;
		return res;
	}
	case KEY_BACKSPACE: {
		if (!mCommand.empty())
			mCommand.erase(--mCommand.end());
		return Res::FINE;
	}
	}
	if (' ' <= ch && ch <= '~') {
		mCommand += ch;
		return Res::FINE;
	}
	return Res::NOPE;
}

ParserResult CommandParser::handleCommand() {
	if (mCommand.empty()) return ParserResult::NOPE;
	if (mCommand == "q") return ParserResult::QUIT;
	return ParserResult::UNKNOWN;
}

pair<string, size_t> CommandParser::getTextAndPosition() {
	return make_pair(":"s + mCommand, (size_t)-1);
}
}  // namespace cz::lastaapps::vimxel::vim
