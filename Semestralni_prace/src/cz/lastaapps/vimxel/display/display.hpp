#ifndef H_DISPLAY
#define H_DISPLAY
#include <ncurses.h>

#include <memory>

#include "../table/cellContract.hpp"
#include "../table/coordinate.hpp"
#include "../vim/vimContract.hpp"
#include "colDrawer.hpp"
#include "contentDrawer.hpp"
#include "headerDrawer.hpp"
#include "rowDrawer.hpp"
#include "state.hpp"
#include "vimDrawer.hpp"

using namespace std;
using namespace cz::lastaapps::vimxel;
namespace cz::lastaapps::vimxel::display {

class Display final {
   private:
	// subwindows
	WINDOW *colNamesWin = nullptr, *rowNamesWin = nullptr,
	       *vimWin = nullptr, *contentWin = nullptr, *posWin = nullptr;
	// drawers for the windows
	HeaderDrawer* headerDrawer = nullptr;
	RowDrawer* rowDrawer = nullptr;
	ColDrawer* colDrawer = nullptr;
	ContentDrawer* contentDrawer = nullptr;
	VimDrawer* vimDrawer = nullptr;

	// caches display state
	table::Coordinates mPos, mViewPort;
	// holds display state - position and viewPort + registers for changes
	shared_ptr<State> mState;
	shared_ptr<StateCallback> mStateCallback;
	// updates cell values
	shared_ptr<CellContract> mCellContract;
	// updates vim down bar
	shared_ptr<vim::VimContract> mVimContract;

	/**
	 * @brief Implements display state callback
	 */
	struct DisplayStateCallback final : StateCallback {
		Display* mParent;
		DisplayStateCallback(Display* parent) : mParent(parent) {}
		void onUpdatePos(const table::Coordinates& pos) override;
		void onUpdateViewPort(const table::Coordinates& coord) override;
	};

   public:
	/**
	 * @brief Construct a new Display object
	 *
	 * @param stateCallback for data updates
	 * @param cellContract for cell updates
	 * @param vimContract for vim bar updates
	 */
	Display(
	    shared_ptr<State> stateCallback,
	    shared_ptr<CellContract> cellContract,
	    shared_ptr<vim::VimContract> vimContract);
	Display(const Display& other) = delete;
	Display(Display&& other) = delete;
	Display& operator=(const Display& other) = delete;
	/**
	 * @brief Destroy the Display object
	 * Clears allocated resources
	 */
	~Display();
	/**
	 * @brief Throws away all the windows and drawers and recreates them
	 */
	void recreate();
	/**
	 * @brief Calls draw() on all the drawers + separating lines
	 */
	void draw();

   private:
	// table size constants
	static constexpr size_t cellWidth = 8;
	static constexpr size_t cellHeight = 1;
	static constexpr size_t colNamesHeight = 1;
	static constexpr size_t rowNamesWidth = 6;
	static constexpr size_t vimHeight = 1;

	/**
	 * @brief Creates windows and drawers
	 */
	void updateDisplayConfig();
	/**
	 * @brief Clears drawers and windows
	 */
	void delWindows();
	/**
	 * @brief Get the Terminal size
	 * @return table::Coordinates size of terminal chars
	 */
	table::Coordinates getTerminalSize();
	/**
	 * @brief Draws lines separating table parts
	 */
	void drawSeparatingLines();
	/**
	 * @brief Checks if viewport enables selected postion to be shown
	 * if not, it updates the viewport accordingly
	 */
	void updateViewPort();
	/**
	 * @brief Clears windows and recreates them
	 */
	void refreshWindows();
};
}  // namespace cz::lastaapps::vimxel::display
#endif