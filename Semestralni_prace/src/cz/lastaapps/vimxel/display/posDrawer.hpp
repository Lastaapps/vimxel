#ifndef POS_DRAWER_H
#define POS_DRAWER_H
#include <ncurses.h>

#include "../table/coordinate.hpp"
#include "drawer.hpp"
using namespace std;
using namespace cz::lastaapps::vimxel;
namespace cz::lastaapps::vimxel::display {
class PosDrawer final : public Drawer {
   public:
	PosDrawer(WINDOW* w);
	PosDrawer(
	    WINDOW* w,
	    table::Coordinates pos, table::Coordinates viewPort);
	void draw() override;
};
}  // namespace cz::lastaapps::vimxel::display
#endif