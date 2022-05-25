
#include "drawer.hpp"

#include <ncurses.h>

#include "../table/coordinate.hpp"
using namespace std;
using namespace cz::lastaapps::vimxel;
namespace cz::lastaapps::vimxel::display {
Drawer::Drawer(WINDOW* w)
    : mWin(w), mWinSize(getWindowSize(w)) {}

PosDrawer::PosDrawer(WINDOW* w)
    : Drawer(w) {}
PosDrawer::PosDrawer(WINDOW* w, table::Coordinates pos, table::Coordinates viewPort)
    : Drawer(w), mPos(pos), mViewPort(viewPort) {}

void PosDrawer::selectPos(
    const table::Coordinates& pos,
    const table::Coordinates& viewPort) {
	mPos = pos;
	mViewPort = viewPort;
	draw();
}

BoxDrawer::BoxDrawer(WINDOW* w) : PosDrawer(w) {}
BoxDrawer::BoxDrawer(WINDOW* w, table::Coordinates pos, table::Coordinates viewPort)
    : PosDrawer(w, pos, viewPort) {}
void BoxDrawer::selectPos(
    const table::Coordinates& pos,
    const table::Coordinates& viewPort) {
	if (mViewPort != viewPort) {
		deselect();
		mPos = pos;
		mViewPort = viewPort;
		drawItems();
		select();
	} else {
		if (mPos != pos) {
			deselect();
			mPos = pos;
			select();
		}
	}
}
void BoxDrawer::deselect() {
	size_t selectedIndex;
	if (!indexOfSelected(selectedIndex)) return;
	renderItem(selectedIndex);
	wrefresh(mWin);
}
void BoxDrawer::select() {
	size_t selectedIndex;
	if (!indexOfSelected(selectedIndex)) return;
	wattron(mWin, A_STANDOUT);
	renderItem(selectedIndex);
	wattroff(mWin, A_STANDOUT);
	wrefresh(mWin);
}

table::Coordinates Drawer::getWindowSize(WINDOW* win) {
	int x, y;
	getmaxyx(win, y, x);
	return table::Coordinates(x, y);
}
}  // namespace cz::lastaapps::vimxel::display