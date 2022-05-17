#ifndef H_PARSER
#define H_PARSER
#include <ncurses.h>

#include <list>
#include <memory>
#include <string>

#include "../display/state.hpp"
#include "../table/table.hpp"
#include "commandParser.hpp"
#include "errorParser.hpp"
#include "insertParser.hpp"
#include "normalParser.hpp"
#include "parserResult.hpp"
#include "vimContract.hpp"
#include "vimState.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {

/**
 * @brief Handles keyboard input and vim modes/state
 * Comunicates with Display and other app components
 */
class VimParser final {
	/**
	 * @brief current internal shared state
	 */
	VimState mState;
	/**
	 * @brief current Vi mode
	 */
	Mode mMode = Mode::NORMAL;

	/**
	 * @brief fetches data like position or viewport from display state
	 */
	shared_ptr<display::StateCallback> mDisplayStateCallback;
	/**
	 * @brief All the contracts for text and cursor output of this parser
	 */
	list<shared_ptr<VimContract>> mContracts;

	// individual parsers
	NormalParser normalParser = NormalParser(&mState);
	InsertParser insertParser = InsertParser(&mState);
	CommandParser commandParser = CommandParser(&mState);
	ErrorParser errorParser = ErrorParser(&mState);

	/**
	 * @brief Implementation of StateCallback to be used inside a parser
	 */
	struct VimStateCallback final : public display::StateCallback {
		// parser to update
		VimParser* mParent;
		VimStateCallback(VimParser* parent) : mParent(parent){};
		void onUpdatePos(const table::Coordinates& pos) override;
		void onUpdateViewPort(const table::Coordinates& viewPort) override;
	};

   public:
	/**
	 * @brief Construct a new Vim Parser object
	 *
	 * @param state shared display state
	 * @param table shared data source
	 * @param filename file we are working with, "" means no file is loaded
	 */
	VimParser(
	    shared_ptr<display::State> state,
	    shared_ptr<table::Table> table,
	    const string& filename);

	/**
	 * @brief Should be called in loop, checks if new key is pressed
	 *
	 * @return how key was handled, how should app lifecycle respond
	 */
	ParserResult handleKeyBoard();

	/**
	 * @brief Creates a contract for observing parser text output
	 *
	 * @return a new contract
	 */
	shared_ptr<VimContract> createContract();
	/**
	 * @brief Used to show an error generated outside the parser
	 */
	void passExternalError(const string& message);

   private:
	/**
	 * @brief Gets the current selected parser
	 * @return selected parser
	 */
	AbsParser& getParser();
	/**
	 * @brief Updates current selected position in state
	 *
	 * @param coord a new selected position
	 */
	void setPos(const table::Coordinates& coord);
	/**
	 * @brief Updates current viewport in state
	 *
	 * @param coord a new viewport
	 */
	void setViewPort(const table::Coordinates& coord);
	/**
	 * @brief New state, update all the observers
	 *
	 * @param info new state representation
	 */
	void notifyContracts(const VimInfo& info);
	/**
	 * @brief Fetch info from the currently selected parser
	 */
	void updateInfo();
	/**
	 * @brief Create new info after unknown command/keysequence was entered
	 */
	void unknowsInfo();
};
}  // namespace cz::lastaapps::vimxel::vim

#endif