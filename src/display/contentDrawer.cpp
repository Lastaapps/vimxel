#include "contentDrawer.hpp"

namespace cz::lastaapps::vimxel::display {

ContentDrawer::ContentDrawer(
    WINDOW* w,
    const size_t colW, const size_t rowH,
    shared_ptr<CellContract> ptr)
    : PosDrawer(w), mColWidth(colW), mRowHeight(rowH), mCntr(ptr) { init(); }

ContentDrawer::ContentDrawer(
    WINDOW* w,
    const size_t colW, const size_t rowH,
    table::Coordinates pos, table::Coordinates viewPort, shared_ptr<CellContract> ptr)
    : PosDrawer(w, pos, viewPort), mColWidth(colW), mRowHeight(rowH), mCntr(ptr) { init(); }

ContentDrawer::~ContentDrawer() {
	mCntr->unregisterCallback();
}
void ContentDrawer::init() {
	mCntr->registerCallback(
	    [this](const Coordinates& coord) {
		    renderItem(coord);
		    wrefresh(mWin);
	    });
}
void ContentDrawer::selectPos(
    const table::Coordinates& pos,
    const table::Coordinates& viewPort) {
	if (mViewPort != viewPort) {
		mPos = pos;
		mViewPort = viewPort;
		draw();
	} else {
		Coordinates old = mPos;
		mPos = pos;
		renderItem(old);
		renderItem(mPos);
	}
	wrefresh(mWin);
}
void ContentDrawer::draw() {
	const size_t vX = mViewPort.x();
	const size_t vY = mViewPort.y();
	for (size_t x = 0; x < cellCount.x(); x++)
		for (size_t y = 0; y < cellCount.y(); y++)
			renderItem(Coordinates(x + vX, y + vY));
	wrefresh(mWin);
}
Coordinates ContentDrawer::getCellsCount() const {
	return Coordinates(mWinSize.x() / mColWidth, mWinSize.y() / mRowHeight);
}
void ContentDrawer::renderItem(const Coordinates& coord) {
	const Coordinates point = getRealPoint(coord);
	const string content = mCntr->getDataAt(coord);
	const bool selected = isSelected(coord);
	if (selected) wattron(mWin, A_STANDOUT);
	mvwprintw(mWin, point.y(), point.x(), "%*.*s", static_cast<int>(mColWidth), static_cast<int>(mColWidth), content.c_str());
	wattroff(mWin, A_STANDOUT);
}
bool ContentDrawer::isSelected(const Coordinates& coord) {
	return mPos.x() == coord.x() && mPos.y() == coord.y();
}
Coordinates ContentDrawer::getRealPoint(const Coordinates& coord) {
	const Coordinates diff = coord - mViewPort;
	return Coordinates(diff.x() * mColWidth, diff.y() * mRowHeight);
}

}  // namespace cz::lastaapps::vimxel::display