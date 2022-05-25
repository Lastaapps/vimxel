#ifndef H_NORMAL_PARSER
#define H_NORMAL_PARSER
#include "absParser.hpp"
#include "parserResult.hpp"
#include "vimState.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {

using Res = ParserResult;
/**
 * @brief Handles key input in NORMAL mode
 * Normal mode means moving in table between cells
 */
class NormalParser final : public AbsParser {
   private:
	// shared main parser state
	VimState* mState;

   public:
	/**
	 * @brief Construct a new Normal Parser object
	 *
	 * @param state shared parser state
	 */
	NormalParser(VimState* state);
	/**
	 * @brief Checks for and manages input in Normal mode
	 *
	 * @param outMode next mode
	 * @return resutl based on key pressed
	 */
	ParserResult handleKey(Mode& outMode) override;
	/**
	 * @brief Shows the content of currently selected cell without cursor
	 * content is the real text/expression, not a calculated value
	 *
	 * @return cell content
	 */
	pair<string, size_t> getTextAndPosition() override;
};
}  // namespace cz::lastaapps::vimxel::vim

#endif