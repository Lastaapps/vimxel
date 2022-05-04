#ifndef H_INSERT_PARSER
#define H_INSERT_PARSER
#include "absParser.hpp"
#include "vimState.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {
class InsertParser final : public AbsParser {
    private:
    string mHistory;
    VimState* mState;
    public:
    InsertParser(VimState* state);
    ParserResult handleKey(Mode & outMode) override;
    pair<string, size_t> getTextAndPosition() override;
};
}

#endif