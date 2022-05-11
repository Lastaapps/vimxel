#ifndef H_ERROR_PARSER
#define H_ERROR_PARSER
#include "absParser.hpp"
#include "vimState.hpp"
#include "parserResult.hpp"
#include "../table/coordinate.hpp"

#include <ncurses.h>

using namespace std;
namespace cz::lastaapps::vimxel::vim {
using Res = ParserResult;
class ErrorParser final : public AbsParser {
    private:
    VimState* mState;
    public:
    ErrorParser(VimState* state);
    Res handleKey(Mode & outMode) override;
    pair<string, size_t> getTextAndPosition() override;
};
}

#endif