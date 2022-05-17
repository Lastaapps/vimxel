#ifndef H_ABS_PARSER
#define H_ABS_PARSER
#include <string>

#include "mode.hpp"
#include "parserResult.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {
/**
 * @brief Abstract parser, each Vi mode has it's own implementation
 */
class AbsParser {
   public:
	/**
	 * @brief Destroy the Abs Parser object
	 */
	virtual ~AbsParser() = default;
	/**
	 * @brief let's a parser process current ncurses key state
	 *
	 * @param outMode next mode to be checked
	 * @return ParserResult - how did the operation end
	 */
	virtual ParserResult handleKey(Mode& outMode) = 0;
	/**
	 * @brief Output for display::vimdrawer, text and cursor position
	 * position of -1 means cursor is disabled
	 *
	 * @return the text to show and the cursor position
	 */
	virtual pair<string, size_t> getTextAndPosition() = 0;
};
}  // namespace cz::lastaapps::vimxel::vim

#endif