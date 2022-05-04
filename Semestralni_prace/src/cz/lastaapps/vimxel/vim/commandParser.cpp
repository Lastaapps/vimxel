#include <ncurses.h>
#include "commandParser.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {

CommandParser::CommandParser(VimState* state)
    : mState(state) {}

ParserResult CommandParser::handleKey(Mode & outMode) {
	using Res = ParserResult;
	int ch = getch();
	if (ch == ERR) return Res::NOPE;
	return Res::NOPE;
}

pair<string, size_t> CommandParser::getTextAndPosition() {
	return make_pair(mState->mTable -> getCell(mState->mPos).getContent(), (size_t)-1);
}
}
