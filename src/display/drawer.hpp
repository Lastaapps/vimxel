#ifndef H_DRAWER
#define H_DRAWER
#include <ncurses.h>

#include "../table/coordinate.hpp"
using namespace std;
using namespace cz::lastaapps::vimxel;
namespace cz::lastaapps::vimxel::display {

/**
 * @brief Holds common logics for most drawers
 * Drawer is responsible for drawing part of UI
 */
class Drawer {
   protected:
	/**
	 * @brief window to draw into
	 */
	WINDOW* const mWin;
	/**
	 * @brief size of the window given
	 */
	const table::Coordinates mWinSize;

   public:
	/**
	 * @brief Construct a new Drawer object
	 *
	 * @param w window to draw in
	 */
	Drawer(WINDOW* w);
	virtual ~Drawer() = default;
	/**
	 * @brief draws whole area
	 */
	virtual void draw() = 0;

   protected:
	/**
	 * @brief Get the window size
	 *
	 * @param win window to get size of
	 * @return table::Coordinates size of the window
	 */
	static table::Coordinates getWindowSize(WINDOW* win);
};

/**
 * @brief Represents drawers with position and viewport
 */
class PosDrawer : public Drawer {
   protected:
	/**
	 * @brief position of selected item and viewport
	 */
	table::Coordinates mPos, mViewPort;

   public:
	/**
	 * @brief Construct a new PosDrawer object
	 *
	 * @param w window to draw in
	 */
	PosDrawer(WINDOW* w);
	/**
	 * @brief Construct a new PosDrawer object
	 *
	 * @param w window to draw in
	 * @param pos selected position
	 * @param viewPort viewport
	 */
	PosDrawer(WINDOW* w, table::Coordinates pos, table::Coordinates viewPort);

	/**
	 * @brief selects new position of viewport
	 *
	 * @param pos new position
	 * @param viewPort new viewport
	 */
	virtual void selectPos(
	    const table::Coordinates& pos,
	    const table::Coordinates& viewPort);
};

/**
 * @brief Implements some common functions for row/column drawers
 */
class BoxDrawer : public PosDrawer {
   public:
	/**
	 * @brief Construct a new Box Drawer object
	 *
	 * @param w window to draw into
	 */
	BoxDrawer(WINDOW* w);
	/**
	 * @brief Construct a new Box Drawer object
	 *
	 * @param w window to draw into
	 * @param pos selected item potion
	 * @param viewPort initial viewport
	 */
	BoxDrawer(WINDOW* w, table::Coordinates pos, table::Coordinates viewPort);

	/**
	 * @brief selects new position of viewport
	 *
	 * @param pos new position
	 * @param viewPort new viewport
	 */
	void selectPos(
	    const table::Coordinates& pos,
	    const table::Coordinates& viewPort) override;

   protected:
	/**
	 * @brief Rerenders item that was selected
	 */
	virtual void deselect();
	/**
	 * @brief Rerenders item that is selected
	 */
	virtual void select();
	/**
	 * @brief Draws all the items
	 */
	virtual void drawItems() = 0;
	/**
	 * @brief renders one item
	 * @param index index of the item
	 */
	virtual void renderItem(size_t index) = 0;
	/**
	 * @brief checks if item on an index is selected
	 *
	 * @param index index of an item
	 * @return true if the item is selected
	 * @return false if it is not
	 */
	virtual bool indexOfSelected(size_t& index) const = 0;
};
}  // namespace cz::lastaapps::vimxel::display
#endif