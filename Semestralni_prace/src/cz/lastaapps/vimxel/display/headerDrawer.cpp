#include "headerDrawer.hpp"

#include <ncurses.h>

#include "../table/coordinate.hpp"
using namespace std;
using namespace cz::lastaapps::vimxel;
namespace cz::lastaapps::vimxel::display {
HeaderDrawer::HeaderDrawer(WINDOW* w)
    : Drawer(w) {}

void HeaderDrawer::draw() {
	mvwprintw(mWin, 0, 0, "VimXel");
	wrefresh(mWin);
}
}  // namespace cz::lastaapps::vimxel::display