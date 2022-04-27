#include "display.hpp"

#include <ncurses.h>

#include "../table/coordinate.hpp"

using namespace std;
using namespace cz::lastaapps::vimxel;
namespace cz::lastaapps::vimxel::display {

Display::Display(shared_ptr<CellContract> contract)
	: mContract(contract) {
	// initial refresh
	refresh();
	updateDisplayConfig();
}

Display::~Display() {
	delWindows();
}

void Display::delWindows() {
	delete posDrawer;
	delete rowDrawer;
	delete colDrawer;
	delete contentDrawer;
	delwin(colNamesWin);
	delwin(rowNamesWin);
	delwin(vimWin);
	delwin(contentWin);
	delwin(posWin);
}
void Display::updateDisplayConfig() {
	const table::Coordinates scrSize = getTerminalSize();

	delWindows();
	colNamesWin = newwin(
	    colNamesHeight,
	    scrSize.x() - rowNamesWidth - 1,
	    0, rowNamesWidth + 1);
	rowNamesWin = newwin(
	    scrSize.y() - 2 - colNamesHeight - vimHeight,
	    rowNamesWidth,
	    colNamesHeight + 1, 0);
	vimWin = newwin(
	    vimHeight, scrSize.x(),
	    scrSize.y() - vimHeight, 0);
	contentWin = newwin(
	    scrSize.y() - 2 - colNamesHeight - vimHeight,
	    scrSize.x() - rowNamesWidth - 1,
	    colNamesHeight + 1, rowNamesWidth + 1);
	posWin = newwin(1, rowNamesWidth, 0, 0);

	posDrawer = new PosDrawer(posWin, mPos, mViewPort);
	rowDrawer = new RowDrawer(rowNamesWin, mPos, mViewPort);
	colDrawer = new ColDrawer(colNamesWin, cellWidth, mPos, mViewPort);
	contentDrawer = new ContentDrawer(contentWin, cellWidth, cellHeight, mPos, mViewPort, mContract);
}
void Display::draw() {
	drawSeparatingLines();
	posDrawer->draw();
	rowDrawer->draw();
	colDrawer->draw();
	contentDrawer->draw();

	while (true) {
		int ch = getch();
		if (ch == ERR) break;
		if (ch == 'q') break;
		switch (ch) {
		case 'k':
			moveY(false);
			break;
		case 'j':
			moveY(true);
			break;
		case 'h':
			moveX(false);
			break;
		case 'l':
			moveX(true);
			break;
		case KEY_UP:
			moveViewY(false);
			break;
		case KEY_DOWN:
			moveViewY(true);
			break;
		case KEY_LEFT:
			moveViewX(false);
			break;
		case KEY_RIGHT:
			moveViewX(true);
			break;
		}
	}
}
void Display::setPosition(const table::Coordinates& coord) {
	mPos = coord;
	updateViewPort();
	refreshWindows();
}
void Display::moveX(bool down) {
	setPosition(down ? mPos.incX() : mPos.decX());
}
void Display::moveY(bool right) {
	setPosition(right ? mPos.incY() : mPos.decY());
}
void Display::updateViewPort() {
	const table::Coordinates scrSize = getTerminalSize();
	const size_t horItems = (scrSize.x() - 1 - rowNamesWidth) / cellWidth - 1;
	if (mPos.x() < mViewPort.x()) {
		mViewPort = mViewPort.withX(mPos.x());
	} else if (mPos.x() > mViewPort.x() + horItems) {
		mViewPort = mViewPort.withX(mPos.x() - horItems);
	}
	const size_t vertItems = scrSize.y() - 2 - 2 - 1;
	if (mPos.y() < mViewPort.y()) {
		mViewPort = mViewPort.withY(mPos.y());
	} else if (mPos.y() > mViewPort.y() + vertItems) {
		mViewPort = mViewPort.withY(mPos.y() - vertItems);
	}
}
void Display::setViewPort(const table::Coordinates& coord) {
	mViewPort = coord;
	refreshWindows();
}
void Display::moveViewX(bool down) {
	setViewPort(down ? mViewPort.incX() : mViewPort.decX());
}
void Display::moveViewY(bool right) {
	setViewPort(right ? mViewPort.incY() : mViewPort.decY());
}

table::Coordinates Display::getTerminalSize() {
	int x, y;
	getmaxyx(stdscr, y, x);
	return table::Coordinates(x, y);
}
void Display::drawSeparatingLines() {
	const table::Coordinates scrSize = getTerminalSize();
	mvhline(colNamesHeight, 0, 0, scrSize.x());
	mvhline(scrSize.y() - vimHeight - 1, 0, 0, scrSize.x());
	mvvline(0, rowNamesWidth, 0, scrSize.y() - 1);
	mvaddch(colNamesHeight, rowNamesWidth, ACS_PLUS);
	mvaddch(scrSize.y() - vimHeight - 1, rowNamesWidth, ACS_BTEE);
	move(0, 0);
}
void Display::refreshWindows() {
	posDrawer->selectPos(mPos, mViewPort);
	rowDrawer->selectPos(mPos, mViewPort);
	colDrawer->selectPos(mPos, mViewPort);
	contentDrawer->selectPos(mPos, mViewPort);
}
}  // namespace cz::lastaapps::vimxel::display