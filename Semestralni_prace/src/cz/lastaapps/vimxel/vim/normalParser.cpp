#include "normalParser.hpp"
#include <ncurses.h>
#include <string>

using namespace std;
namespace cz::lastaapps::vimxel::vim {

NormalParser::NormalParser(VimState* state)
    : mState(state) {}

ParserResult NormalParser::handleKey(Mode & outMode) {
	using Res = ParserResult;
	int ch = getch();
	if (ch == ERR) return Res::NOPE;
	switch (ch) {
	case ':':
		outMode = Mode::COMMAND;
		return Res::FINE;
	case 'i':
	case 'a':
	case KEY_F0 + 2:
		outMode = Mode::INSERT;
		return Res::FINE;
	case 'k':
		mState -> mDisplayState->moveY(false);
		return Res::FINE;
	case 'j':
	case '\n':
		mState -> mDisplayState->moveY(true);
		return Res::FINE;
	case 'h':
	case KEY_STAB:
	case KEY_BTAB:
		mState -> mDisplayState->moveX(false);
		return Res::FINE;
	case 'l':
	case '\t':
		mState -> mDisplayState->moveX(true);
		return Res::FINE;
	case KEY_UP:
		mState -> mDisplayState->moveViewY(false);
		return Res::FINE;
	case KEY_DOWN:
		mState -> mDisplayState->moveViewY(true);
		return Res::FINE;
	case KEY_LEFT:
		mState -> mDisplayState->moveViewX(false);
		return Res::FINE;
	case KEY_RIGHT:
		mState -> mDisplayState->moveViewX(true);
		return Res::FINE;
	case 'x': {
		mState -> mTable -> updateCell(mState -> mPos, table::EmptyCell());
		return Res::FINE;
	}
	}
	return Res::NOPE;
}

pair<string, size_t> NormalParser::getTextAndPosition() {
	return make_pair(mState->mTable -> getCell(mState->mPos).getContent(), (size_t)-1);
}
}