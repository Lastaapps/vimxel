#ifndef H_INSERT_PARSER
#define H_INSERT_PARSER
#include "../table/coordinate.hpp"
#include "absParser.hpp"
#include "parserResult.hpp"
#include "vimState.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {

using Res = ParserResult;
/**
 * @brief Insert mode parser - handles cell editing
 */
class InsertParser final : public AbsParser {
   private:
	// new cell content
	string mText = "";
	// cursor position
	size_t mCursor = (size_t)-1;
	// currently edited cell
	table::Coordinates mPos;
	// shared parrent parser state
	VimState* mState;

   public:
	/**
	 * @brief Construct a new Insert Parser object
	 *
	 * @param state shared parser state
	 */
	InsertParser(VimState* state);
	/**
	 * @brief Moves thourough cell and edits it, saves or throws away content in the end
	 *
	 * @param outMode next mode is saved here
	 * @return handled result
	 */
	Res handleKey(Mode& outMode) override;
	/**
	 * @brief Current editing state report
	 *
	 * @return currently edited text and cursor position
	 */
	pair<string, size_t> getTextAndPosition() override;

   private:
	bool checkLoad();
};
}  // namespace cz::lastaapps::vimxel::vim

#endif