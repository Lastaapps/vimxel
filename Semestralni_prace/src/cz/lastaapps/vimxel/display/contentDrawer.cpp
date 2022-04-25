#include "contentDrawer.hpp"

namespace cz::lastaapps::vimxel::display {

ContentDrawer::ContentDrawer(
    WINDOW* w,
    const size_t colW, const size_t rowH,
    shared_ptr<CellContract> ptr)
    : Drawer(w), mColWidth(colW), mRowHeight(rowH), mCntr(ptr) { init(); }

ContentDrawer::ContentDrawer(
    WINDOW* w,
    const size_t colW, const size_t rowH,
    table::Coordinates pos, table::Coordinates viewPort, shared_ptr<CellContract> ptr)
    : Drawer(w, pos, viewPort), mColWidth(colW), mRowHeight(rowH), mCntr(ptr) { init(); }

ContentDrawer::~ContentDrawer() {
    mCntr->unregisterCallback();
}
void ContentDrawer::init() {
	mCntr->registerCallback(
	    [this](const Coordinates& coord) { renderItem(coord); });
}
void ContentDrawer::draw() {
}
inline Coordinates ContentDrawer::getCellsCount() const {
    return Coordinates(mWinSize.x() / mColWidth, mWinSize.y() / mRowHeight);
}
inline void ContentDrawer::renderItem(const Coordinates& coord) {
    const Coordinates point = getRealPoint(coord);
    const string content = mCntr -> getDataAt(coord);
    const bool selected = isSelected(coord);
    if (selected) wattron(mWin, A_STANDOUT);
    mvwprintw(mWin, point.y(), point.x(), "%.*s", (int)mColWidth, content.c_str());
    wattroff(mWin, A_STANDOUT);
}
inline bool ContentDrawer::isSelected(const Coordinates& coord) {
    return mPos.x() == coord.x() && mPos.y() == coord.y();
}
Coordinates ContentDrawer::getRealPoint(const Coordinates& coord) {
    const Coordinates diff = coord - mViewPort;
    return Coordinates(diff.x() * mColWidth, diff.y() * mRowHeight);
}

}  // namespace cz::lastaapps::vimxel::display