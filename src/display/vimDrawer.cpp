#include "vimDrawer.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::display {
VimDrawer::VimDrawer(WINDOW* w, shared_ptr<vim::VimContract> contract)
    : Drawer(w), mContract(contract) {
	mContract->registerCallback(
	    [&](const vim::VimInfo& info) {
		    updateInfo(info);
	    });
}

void VimDrawer::updateInfo(const vim::VimInfo& info) {
	mInfo = info;
	draw();
}

void VimDrawer::draw() {
	mvwprintw(mWin, 0, 0, "%*s", static_cast<int>(mWinSize.x()), "");
	if (!mInfo.text.empty()) {
		mvwprintw(mWin, 0, 0, "%.*s", static_cast<int>(mWinSize.x()), mInfo.text.c_str());
		if (mInfo.cursorPos != (size_t)-1) {
			wattron(mWin, A_STANDOUT);
			if (mInfo.cursorPos < mInfo.text.length())
				mvwaddch(mWin, 0, static_cast<int>(mInfo.cursorPos), mInfo.text.at(mInfo.cursorPos));
			else
				mvwaddch(mWin, 0, static_cast<int>(mInfo.cursorPos), ' ');
			wattroff(mWin, A_STANDOUT);
		}
	}
	const string mode = to_string(mInfo.mode);
	if (!mode.empty()) {
		const size_t pos = mWinSize.x() - mode.length();
		wattron(mWin, A_STANDOUT);
		mvwprintw(mWin, 0, pos, "%s", mode.c_str());
		wattroff(mWin, A_STANDOUT);
	}
	wrefresh(mWin);
}
}  // namespace cz::lastaapps::vimxel::display
