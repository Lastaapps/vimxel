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
	case 'k':
		mState -> mDisplayState->moveY(false);
		break;
	case 'j':
		mState -> mDisplayState->moveY(true);
		break;
	case 'h':
		mState -> mDisplayState->moveX(false);
		break;
	case 'l':
		mState -> mDisplayState->moveX(true);
		break;
	case KEY_UP:
		mState -> mDisplayState->moveViewY(false);
		break;
	case KEY_DOWN:
		mState -> mDisplayState->moveViewY(true);
		break;
	case KEY_LEFT:
		mState -> mDisplayState->moveViewX(false);
		break;
	case KEY_RIGHT:
		mState -> mDisplayState->moveViewX(true);
		break;
	}
	return Res::NOPE;
}

pair<string, size_t> NormalParser::getTextAndPosition() {
	return make_pair(mState->mTable -> getCell(mState->mPos).getContent(), (size_t)-1);
}
}