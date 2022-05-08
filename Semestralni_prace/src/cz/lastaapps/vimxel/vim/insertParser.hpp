#ifndef H_INSERT_PARSER
#define H_INSERT_PARSER
#include "absParser.hpp"
#include "vimState.hpp"
#include "parserResult.hpp"
#include "../table/coordinate.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {
using Res = ParserResult;
class InsertParser final : public AbsParser {
    private:
    string mText = "";
    size_t mCursor = (size_t)-1;
    table::Coordinates mPos;
    VimState* mState;
    public:
    InsertParser(VimState* state);
    Res handleKey(Mode & outMode) override;
    pair<string, size_t> getTextAndPosition() override;

   private:
	void saveContent();
	bool checkLoad();
};
}

#endif