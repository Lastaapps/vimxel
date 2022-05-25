#ifndef H_ERROR_PARSER
#define H_ERROR_PARSER
#include <ncurses.h>

#include "../table/coordinate.hpp"
#include "absParser.hpp"
#include "parserResult.hpp"
#include "vimState.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {

using Res = ParserResult;

/**
 * @brief Temporary mode, that just shows an error and consumese 1 key press
 */
class ErrorParser final : public AbsParser {
   private:
	// common shared state
	VimState* mState;

   public:
	/**
	 * @brief Construct a new Error Parser object
	 *
	 * @param state shared parser state
	 */
	ErrorParser(VimState* state);
	/**
	 * @brief Just consumes first key pressed and then switches to mState.mResultMode
	 *
	 * @param outMode is changed to mState.mResultMode
	 * @return ParserResult::UPDATE
	 */
	Res handleKey(Mode& outMode) override;
	/**
	 * @brief Just the error message and no cursor
	 *
	 * @return the error message and hidden cursor
	 */
	pair<string, size_t> getTextAndPosition() override;
};
}  // namespace cz::lastaapps::vimxel::vim

#endif