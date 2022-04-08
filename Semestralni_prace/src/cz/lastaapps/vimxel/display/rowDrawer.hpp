#ifndef ROW_DRAWER_H
#define ROW_DRAWER_H
#include <ncurses.h>

#include "../table/coordinate.hpp"
#include "drawer.hpp"
using namespace std;
using namespace cz::lastaapps::vimxel;
namespace cz::lastaapps::vimxel::display {
class RowDrawer final : public BoxDrawer {
   public:
	RowDrawer(WINDOW* w);
	RowDrawer(
	    WINDOW* w,
	    table::Coordinates pos, table::Coordinates viewPort);
	void draw() override;

   protected:
	void drawItems() override;
	inline void renderItem(size_t index) override;
	bool indexOfSelected(size_t& index) const override;
};
}  // namespace cz::lastaapps::vimxel::display
#endif