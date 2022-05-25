#include "vimContract.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {

VimInfo::VimInfo() : VimInfo(0, "", Mode::NONE) {}
VimInfo::VimInfo(size_t cP, const string& s, Mode m)
    : cursorPos(cP), text(s), mode(m) {}

void VimContract::onDataChanged(const VimInfo& info) {
	if (mHasCallback)
		mCallback(info);
	mLatest = info;
}
void VimContract::registerCallback(Callback c) {
	mHasCallback = true;
	mCallback = c;
	c(mLatest);
}
void VimContract::unregisterCallback() {
	mHasCallback = false;
}
}  // namespace cz::lastaapps::vimxel::vim
