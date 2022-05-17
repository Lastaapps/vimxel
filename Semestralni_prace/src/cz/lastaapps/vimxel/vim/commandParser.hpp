#ifndef H_COMMAND_PARSER
#define H_COMMAND_PARSER
#include "absParser.hpp"
#include "vimState.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {

using Res = vim::ParserResult;

/**
 * @brief Handles command input
 */
class CommandParser final : public AbsParser {
   private:
	// command buffer
	string mCommand = "";
	// shared state
	VimState* mState;

   public:
	/**
	 * @brief Construct a new Command Parser object
	 *
	 * @param state shared parser state
	 */
	CommandParser(VimState* state);
	/**
	 * @brief Adds a char to buffer, deletes it ot tries to execute command
	 *
	 * @param outMode next mode, error or normal
	 * @return resutl depending of key pressed
	 */
	ParserResult handleKey(Mode& outMode) override;
	/**
	 * @brief Currently prepared command + ':' at the beginning
	 *
	 * @return current state of command
	 */
	pair<string, size_t> getTextAndPosition() override;

   private:
	/**
	 * @brief Enter has just been pressed, we are trying to find the valid interpretation
	 *
	 * @param outMode next mode, error or normal
	 * @return UNKNOWN, ERROR, QUIT or UPDATE
	 */
	Res handleCommand(Mode& outMode);
	/**
	 * @brief Tryies to handle :w and :q based command
	 *
	 * @param outMode next mode
	 * @return UNKNOWN when no command is matched, others when found
	 */
	Res tryQuitAndWrite(Mode& outMode);
	/**
	 * @brief Tries to match :o commands
	 *
	 * @param outMode next mode
	 * @return UNKNOWN when no command is matched, others when found
	 */
	Res tryOpenFile(Mode& outMode);
	/**
	 * @brief Tryies to handle :exp command
	 *
	 * @param outMode next mode
	 * @return UNKNOWN when no command is matched, others when found
	 */
	Res tryExportFile(Mode& outMode);
	/**
	 * @brief Tries to match :A1 to jump to
	 *
	 * @param outMode next mode
	 * @return UNKNOWN when no command is matched, others when found
	 */
	Res tryJump(Mode& outMode);
};
}  // namespace cz::lastaapps::vimxel::vim

#endif