#ifndef H_COL_DRAWER
#define H_COL_DRAWER
#include <ncurses.h>

#include "../table/coordinate.hpp"
#include "drawer.hpp"
using namespace std;
using namespace cz::lastaapps::vimxel;
namespace cz::lastaapps::vimxel::display {

/**
 * @brief This component is responsible for drawing column names
 */
class ColDrawer final : public BoxDrawer {
   private:
	size_t mWidth;

   public:
	/**
	 * @brief Construct a new Col Drawer object
	 *
	 * @param w window to draw in
	 * @param width width of each column
	 */
	ColDrawer(WINDOW* w, size_t width);
	/**
	 * @brief Construct a new Col Drawer object
	 *
	 * @param w window to draw in
	 * @param width width of each column
	 * @param pos starting selection position
	 * @param viewPort starting viewport position
	 */
	ColDrawer(
	    WINDOW* w, size_t width,
	    table::Coordinates pos, table::Coordinates viewPort);
	/**
	 * @brief Redraws all the column names
	 */
	void draw() override;

   protected:
	/**
	 * @brief Redraws all the items
	 */
	void drawItems() override;
	/**
	 * @brief Renders only one item (including selection)
	 *
	 * @param index index of the item to redraw (not relative to position)
	 */
	inline void renderItem(size_t index) override;
	/**
	 * @brief Clears area, where would be column name rendered
	 *
	 * @param index index of the item to clear
	 */
	inline void renderEmpty(size_t index);
	/**
	 * @brief Checks if item is selected or not
	 *
	 * @param index index of the item to check
	 * @return true if the item is selected
	 * @return false if it is not
	 */
	bool indexOfSelected(size_t& index) const override;
};
}  // namespace cz::lastaapps::vimxel::display
#endif