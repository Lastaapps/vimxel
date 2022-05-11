#ifndef H_CONTENT_DRAWER
#define H_CONTENT_DRAWER

#include <ncurses.h>

#include <memory>

#include "../table/cellContract.hpp"
#include "../table/coordinate.hpp"
#include "drawer.hpp"
using namespace std;
using namespace cz::lastaapps::vimxel;
using namespace cz::lastaapps::vimxel::table;
namespace cz::lastaapps::vimxel::display {

/**
 * @brief Drawer the content of a table, all the cells
 */
class ContentDrawer final : public PosDrawer {
	const size_t mColWidth, mRowHeight;
	/**
	 * @brief Provides data updates from data storage
	 */
	const shared_ptr<CellContract> mCntr;
	/**
	 * @brief Window size in cell
	 */
	const Coordinates cellCount = getCellsCount();

   public:
	/**
	 * @brief Construct a new Content Drawer object
	 *
	 * @param w window to draw in
	 * @param colW width of the columns to draw
	 * @param rowH height of rows
	 * @param cnt contract to obtain data
	 */
	ContentDrawer(WINDOW* w, const size_t colW, const size_t rowH, shared_ptr<CellContract> cnt);
	/**
	 * @brief Construct a new Content Drawer object
	 *
	 * @param w window to draw in
	 * @param colW width of the columns to draw
	 * @param rowH height of rows
	 * @param pos starting selected position
	 * @param viewPort starting viewport
	 * @param cnt contract to obtain data
	 */
	ContentDrawer(
	    WINDOW* w,
	    const size_t colW, const size_t rowH,
	    table::Coordinates pos, table::Coordinates viewPort,
	    shared_ptr<CellContract> cnt);
	/**
	 * @brief Destroy the Content Drawer object
	 * unregisters callback from datasource
	 */
	~ContentDrawer();
	/**
	 * @brief Selects new position / changes viewport
	 *
	 * @param pos new position
	 * @param viewPort new viewport
	 */
	void selectPos(
	    const table::Coordinates& pos,
	    const table::Coordinates& viewPort) override;
	/**
	 * @brief Draws all the cells
	 */
	void draw() override;

   private:
	/**
	 * @brief Gets ready to get data from data source
	 */
	void init();
	/**
	 * @brief computes how many cells are there in a window
	 *
	 * @return number of cells
	 */
	Coordinates getCellsCount() const;
	/**
	 * @brief draws single item at coordinates
	 *
	 * @param coord real coordinates to draw, not cell ones
	 */
	void renderItem(const Coordinates& coord);
	/**
	 * @brief Checks if a cell is selected
	 *
	 * @param coord data cell coordinates
	 * @return true if the cell is selected
	 * @return false if it is not
	 */
	inline bool isSelected(const Coordinates& coord);
	/**
	 * @brief Converts coordinates to cell indexes
	 *
	 * @param coord data cell coordinates
	 * @return Coordinates draw cell coordinates
	 */
	Coordinates getRealPoint(const Coordinates& coord);
};
}  // namespace cz::lastaapps::vimxel::display
#endif