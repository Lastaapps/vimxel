#ifndef H_INSERT_PARSER
#define H_INSERT_PARSER
#include "absParser.hpp"
#include "vimState.hpp"
#include "../table/coordinate.hpp"
#include "../table/cell.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {
class InsertParser final : public AbsParser {
    private:
    string mText = "";
    size_t mCursor = (size_t)-1;
    table::Coordinates mPos;
    VimState* mState;
    public:
    InsertParser(VimState* state);
    ParserResult handleKey(Mode & outMode) override;
    pair<string, size_t> getTextAndPosition() override;

   private:
	void saveContent();
	bool checkLoad();
};
}

#endif