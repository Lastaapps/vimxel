#include <ncurses.h>
#include "insertParser.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {

InsertParser::InsertParser(VimState* state)
    : mState(state) {}

ParserResult InsertParser::handleKey(Mode & outMode) {
	using Res = ParserResult;
	int ch = getch();
	if (ch == ERR) return Res::NOPE;
	return Res::NOPE;
}

pair<string, size_t> InsertParser::getTextAndPosition() {
	return make_pair(mState->mTable -> getCell(mState->mPos).getContent(), (size_t)-1);
}
}
