#include "colDrawer.hpp"

#include <ncurses.h>

#include "../table/coordinate.hpp"
using namespace std;
using namespace cz::lastaapps::vimxel;
namespace cz::lastaapps::vimxel::display {
ColDrawer::ColDrawer(WINDOW* w, size_t width)
    : BoxDrawer(w), mWidth(width) {}
ColDrawer::ColDrawer(WINDOW* w, size_t width, table::Coordinates pos, table::Coordinates viewPort)
    : BoxDrawer(w, pos, viewPort), mWidth(width) {}

void ColDrawer::draw() {
	drawItems();
}

void ColDrawer::drawItems() {
	size_t i = 0;
	for (; i < (mWinSize.x() / mWidth); i++)
		renderItem(i);
	// to remove remaining chars while returning
	renderEmpty(i);
	wrefresh(mWin);
	// to update selection
	select();
}
inline void ColDrawer::renderItem(size_t index) {
	mvwprintw(mWin, 0, index * mWidth, "%*s", static_cast<int>(mWidth), mViewPort.incX(index).xString().c_str());
}
inline void ColDrawer::renderEmpty(size_t index) {
	mvwprintw(mWin, 0, index * mWidth, "%*s", static_cast<int>(mWidth), " ");
}
bool ColDrawer::indexOfSelected(size_t& index) const {
	if (mPos.x() < mViewPort.x()) return false;
	index = mPos.x() - mViewPort.x();
	return index <= mWinSize.x();
}
}  // namespace cz::lastaapps::vimxel::display