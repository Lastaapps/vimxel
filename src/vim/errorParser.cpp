#include "errorParser.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {

ErrorParser::ErrorParser(VimState* state)
    : mState(state) {}

Res ErrorParser::handleKey(Mode& outMode) {
	int ch = getch();
	if (ch == ERR) return Res::NOPE;

	outMode = mState->mReturnMode;
	return Res::UPDATE;
}
pair<string, size_t> ErrorParser::getTextAndPosition() {
	return make_pair(mState->mErrorMsg, -1);
}

}  // namespace cz::lastaapps::vimxel::vim