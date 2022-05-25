#ifndef H_MODE
#define H_MODE
#include <stdexcept>
#include <string>

using namespace std;
namespace cz::lastaapps::vimxel::vim {

/**
 * @brief Vim Modes like Normal, Insert, ...
 */
enum class Mode {
	/**
	 * @brief Invalid mode, used as temporary only
	 */
	NONE,
	/**
	 * @brief Normal mode - browsing table
	 */
	NORMAL,
	/**
	 * @brief Insert mode - editing cell content
	 */
	INSERT,
	/**
	 * @brief Command mode - user is entering a command
	 */
	COMMAND,
	/**
	 * @brief Error mode - an error occurred, message is shown and next key press in consumed
	 */
	ERROR,
};
/**
 * @brief Converts Mode enum items into their string representations
 * all the texts are uppercase
 *
 * @param m mode to get name for
 * @return name to the mode
 */
string to_string(Mode m);
}  // namespace cz::lastaapps::vimxel::vim

#endif