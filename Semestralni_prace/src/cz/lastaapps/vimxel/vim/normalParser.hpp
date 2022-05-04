#ifndef H_NORMAL_PARSER
#define H_NORMAL_PARSER
#include "absParser.hpp"
#include "vimState.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {
class NormalParser final : public AbsParser {
    private:
    string mHistory;
    VimState* mState;
    public:
    NormalParser(VimState* state);
    ParserResult handleKey(Mode & outMode) override;
    pair<string, size_t> getTextAndPosition() override;
};
}

#endif