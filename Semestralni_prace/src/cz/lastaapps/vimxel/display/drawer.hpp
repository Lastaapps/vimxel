#ifndef DRAWER_H
#define DRAWER_H
#include <ncurses.h>

#include "../table/coordinate.hpp"
using namespace std;
using namespace cz::lastaapps::vimxel;
namespace cz::lastaapps::vimxel::display {
class Drawer {
   protected:
	WINDOW* const mWin;
	const table::Coordinates mWinSize;
	table::Coordinates mPos, mViewPort;

   public:
	Drawer(WINDOW* w);
	Drawer(WINDOW* w, table::Coordinates pos, table::Coordinates viewPort);
	virtual ~Drawer();
	virtual void selectPos(
	    const table::Coordinates& pos,
	    const table::Coordinates& viewPort);
	virtual void draw() = 0;

   protected:
	static table::Coordinates getWindowSize(WINDOW* win);
};
class BoxDrawer : public Drawer {
   public:
	BoxDrawer(WINDOW* w);
	BoxDrawer(WINDOW* w, table::Coordinates pos, table::Coordinates viewPort);

	void selectPos(
	    const table::Coordinates& pos,
	    const table::Coordinates& viewPort) override;

   protected:
	virtual void deselect();
	virtual void select();
	virtual void drawItems() = 0;
	virtual void renderItem(size_t index) = 0;
	virtual bool indexOfSelected(size_t& index) const = 0;
};
}  // namespace cz::lastaapps::vimxel::display
#endif