#ifndef H_ROW_DRAWER
#define H_ROW_DRAWER
#include <ncurses.h>

#include "../table/coordinate.hpp"
#include "drawer.hpp"
using namespace std;
using namespace cz::lastaapps::vimxel;
namespace cz::lastaapps::vimxel::display {

/**
 * @brief Draws column with row names
 *
 */
class RowDrawer final : public BoxDrawer {
   public:
	/**
	 * @brief Construct a new Row Drawer object
	 *
	 * @param w window to draw into
	 */
	RowDrawer(WINDOW* w);
	/**
	 * @brief Construct a new Row Drawer object
	 *
	 * @param w windows to draw into
	 * @param pos initial selected item
	 * @param viewPort initial viewport
	 */
	RowDrawer(
	    WINDOW* w,
	    table::Coordinates pos, table::Coordinates viewPort);
	/**
	 * @brief draws all the row names
	 */
	void draw() override;

   protected:
	/**
	 * @brief draws all the row names
	 */
	void drawItems() override;
	/**
	 * @brief render one item
	 *
	 * @param index the index of the item to render
	 */
	inline void renderItem(size_t index) override;
	/**
	 * @brief checks if an item is selected or not
	 *
	 * @param index
	 * @return true
	 * @return false
	 */
	bool indexOfSelected(size_t& index) const override;
};
}  // namespace cz::lastaapps::vimxel::display
#endif