
#ifndef COL_DRAWER_H
#define COL_DRAWER_H
#include <ncurses.h>

#include "../table/coordinate.hpp"
#include "drawer.hpp"
using namespace std;
using namespace cz::lastaapps::vimxel;
namespace cz::lastaapps::vimxel::display {
class ColDrawer final : public BoxDrawer {
   private:
	size_t mWidth;

   public:
	ColDrawer(WINDOW* w, size_t width);
	ColDrawer(
	    WINDOW* w, size_t width,
	    table::Coordinates pos, table::Coordinates viewPort);
	void draw() override;

   protected:
	void drawItems() override;
	inline void renderItem(size_t index) override;
	inline void renderEmpty(size_t index);
	bool indexOfSelected(size_t& index) const override;
};
}  // namespace cz::lastaapps::vimxel::display
#endif