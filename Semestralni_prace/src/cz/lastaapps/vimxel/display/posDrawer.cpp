
#include "posDrawer.hpp"

#include <ncurses.h>

#include "../table/coordinate.hpp"
using namespace std;
using namespace cz::lastaapps::vimxel;
namespace cz::lastaapps::vimxel::display {
PosDrawer::PosDrawer(WINDOW* w)
    : Drawer(w) {}
PosDrawer::PosDrawer(WINDOW* w, table::Coordinates pos, table::Coordinates viewPort)
    : Drawer(w, pos, viewPort) {}

void PosDrawer::draw() {
	mvwprintw(mWin, 0, 0, "VimXel");
	// mvwprintw(mWin, 0, 0, "%3s%3lu", mPos.xString().c_str(), mPos.y());
	wrefresh(mWin);
}
}  // namespace cz::lastaapps::vimxel::display