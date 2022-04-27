#ifndef DISPLAY_H
#define DISPLAY_H
#include <ncurses.h>

#include <memory>

#include "../table/coordinate.hpp"
#include "../table/cellContract.hpp"
#include "colDrawer.hpp"
#include "posDrawer.hpp"
#include "rowDrawer.hpp"
#include "contentDrawer.hpp"
using namespace std;
using namespace cz::lastaapps::vimxel;
namespace cz::lastaapps::vimxel::display {

class Display final {
   private:
	WINDOW *colNamesWin = nullptr, *rowNamesWin = nullptr,
	       *vimWin = nullptr, *contentWin = nullptr, *posWin = nullptr;
	PosDrawer* posDrawer = nullptr;
	RowDrawer* rowDrawer = nullptr;
	ColDrawer* colDrawer = nullptr;
	ContentDrawer* contentDrawer = nullptr;
	table::Coordinates mPos, mViewPort;
	shared_ptr<CellContract> mContract;

   public:
	Display(shared_ptr<CellContract> contract);
	~Display();
	void draw();
	void setPosition(const table::Coordinates& corrd);
	void moveX(bool down);
	void moveY(bool right);
	void setViewPort(const table::Coordinates& corrd);
	void moveViewX(bool down);
	void moveViewY(bool right);

   private:
	static constexpr size_t cellWidth = 8;
	static constexpr size_t cellHeight = 1;
	static constexpr size_t colNamesHeight = 1;
	static constexpr size_t rowNamesWidth = 6;
	static constexpr size_t vimHeight = 1;

	void updateDisplayConfig();
	void delWindows();
	table::Coordinates getTerminalSize();
	void drawSeparatingLines();
	void updateViewPort();
	void refreshWindows();
};
}  // namespace cz::lastaapps::vimxel::display
#endif