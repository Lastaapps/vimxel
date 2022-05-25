#include "display.hpp"

#include <ncurses.h>

#include "../table/coordinate.hpp"

using namespace std;
using namespace cz::lastaapps::vimxel;
namespace cz::lastaapps::vimxel::display {

Display::Display(shared_ptr<State> state,
                 shared_ptr<CellContract> contract,
                 shared_ptr<vim::VimContract> vimContract)
    : mState(state), mCellContract(contract), mVimContract(vimContract) {
	// initial refresh
	refresh();
	updateDisplayConfig();

	mStateCallback = shared_ptr<StateCallback>(new DisplayStateCallback(this));
	mState->registerCallback(mStateCallback);
}

Display::~Display() {
	delWindows();
}

void Display::DisplayStateCallback::onUpdatePos(const table::Coordinates& coord) {
	mParent->mPos = coord;
	mParent->updateViewPort();
	mParent->refreshWindows();
}
void Display::DisplayStateCallback::onUpdateViewPort(const table::Coordinates& coord) {
	mParent->mViewPort = coord;
	mParent->refreshWindows();
}

void Display::delWindows() {
	delete headerDrawer;
	delete rowDrawer;
	delete colDrawer;
	delete contentDrawer;
	delete vimDrawer;
	headerDrawer = nullptr;
	rowDrawer = nullptr;
	colDrawer = nullptr;
	contentDrawer = nullptr;
	vimDrawer = nullptr;
	delwin(colNamesWin);
	delwin(rowNamesWin);
	delwin(vimWin);
	delwin(contentWin);
	delwin(posWin);
}
void Display::updateDisplayConfig() {
	const table::Coordinates scrSize = getTerminalSize();

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

	headerDrawer = new HeaderDrawer(posWin);
	rowDrawer = new RowDrawer(rowNamesWin, mPos, mViewPort);
	colDrawer = new ColDrawer(colNamesWin, cellWidth, mPos, mViewPort);
	contentDrawer = new ContentDrawer(contentWin, cellWidth, cellHeight, mPos, mViewPort, mCellContract);
	vimDrawer = new VimDrawer(vimWin, mVimContract);
}

void Display::recreate() {
	delWindows();
	updateDisplayConfig();
}

void Display::draw() {
	clear();
	refresh();
	drawSeparatingLines();
	headerDrawer->draw();
	rowDrawer->draw();
	colDrawer->draw();
	contentDrawer->draw();
	vimDrawer->draw();
	refresh();
}

void Display::updateViewPort() {
	const table::Coordinates scrSize = getTerminalSize();
	const table::Coordinates original = mViewPort;
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

	if (mViewPort != original)
		mState->setViewPort(mViewPort);
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
	rowDrawer->selectPos(mPos, mViewPort);
	colDrawer->selectPos(mPos, mViewPort);
	contentDrawer->selectPos(mPos, mViewPort);
}
}  // namespace cz::lastaapps::vimxel::display