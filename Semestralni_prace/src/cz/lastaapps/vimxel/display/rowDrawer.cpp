#include "rowDrawer.hpp"

#include <ncurses.h>

#include "../table/coordinate.hpp"
using namespace std;
using namespace cz::lastaapps::vimxel;
namespace cz::lastaapps::vimxel::display {
RowDrawer::RowDrawer(WINDOW* w)
    : BoxDrawer(w) {}
RowDrawer::RowDrawer(WINDOW* w, table::Coordinates pos, table::Coordinates viewPort)
    : BoxDrawer(w, pos, viewPort) {}

void RowDrawer::draw() {
	drawItems();
}

void RowDrawer::drawItems() {
	for (size_t i = 0; i < mWinSize.y(); i++)
		renderItem(i);
	wrefresh(mWin);
	// to update selection
	select();
}
inline void RowDrawer::renderItem(size_t index) {
	mvwprintw(mWin, index, 0, "%*lu", static_cast<int>(mWinSize.x()), mViewPort.y() + index + 1);
}
bool RowDrawer::indexOfSelected(size_t& index) const {
	if (mPos.y() < mViewPort.y()) return false;
	index = mPos.y() - mViewPort.y();
	return index <= mWinSize.y();
}
}  // namespace cz::lastaapps::vimxel::display