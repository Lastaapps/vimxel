#ifndef CONTENT_DRAWER_H
#define CONTENT_DRAWER_H
#include <ncurses.h>
#include <memory>

#include "../table/coordinate.hpp"
#include "../table/cellContract.hpp"
#include "drawer.hpp"
using namespace std;
using namespace cz::lastaapps::vimxel;
using namespace cz::lastaapps::vimxel::table;
namespace cz::lastaapps::vimxel::display {
class ContentDrawer final : public Drawer {
	const size_t mColWidth, mRowHeight;
	const shared_ptr<CellContract> mCntr;
	Coordinates cellCount = getCellsCount();

	public:
	ContentDrawer(WINDOW * w, const size_t colW, const size_t rowH, shared_ptr<CellContract> cnt);
	ContentDrawer(
	    WINDOW* w,
	const size_t colW, const size_t rowH,
	    table::Coordinates pos, table::Coordinates viewPort,
		shared_ptr<CellContract> cnt);
	~ContentDrawer();
	void draw() override;

	private:
	void init();
	inline Coordinates getCellsCount() const;
	inline void renderItem(const Coordinates &coord);
	inline bool isSelected(const Coordinates &coord);
	Coordinates getRealPoint(const Coordinates& coord);
};
}  // namespace cz::lastaapps::vimxel::display
#endif