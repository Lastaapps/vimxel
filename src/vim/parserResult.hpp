#ifndef H_PARSER_RESULT
#define H_PARSER_RESULT

namespace cz::lastaapps::vimxel::vim {

/**
 * @brief Represents the result of the current parser iteration to handle key presses
 */
enum class ParserResult {
	/**
	 * @brief Nothing happened
	 */
	NOPE,
	/**
	 * @brief Unknown operation was executed.
	 * Next keypress should be passed to the current mode
	 * Error message should be saved in a VimState object
	 * New info should be emitted
	 */
	UNKNOWN,
	/**
	 * @brief There was an error while handling a keypress
	 * Next keypress is consumed by ERROR vim mode, others by other
	 * Error message should be saved in a VimState object
	 * New info should be emitted
	 */
	ERROR,
	/**
	 * @brief Internal state was updated
	 * New info should be emitted
	 */
	UPDATE,
	/**
	 * @brief App should quit now
	 */
	QUIT,
};
}

#endif