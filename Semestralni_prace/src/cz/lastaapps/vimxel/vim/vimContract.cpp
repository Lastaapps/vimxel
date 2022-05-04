#include "vimContract.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {

VimInfo::VimInfo() : VimInfo(0, "", Mode::NONE) {}
VimInfo::VimInfo(size_t cP, const string & s, Mode m) 
: cursorPos(cP), text(s), mode(m) {}

void VimContract::onDataChanged(const VimInfo& info) {
    if (hasCallback)
		mCallback(info);
}
void VimContract::registerCallback(Callback c) {
    hasCallback = true;
    mCallback = c;
}
void VimContract::unregisterCallback() {
    hasCallback = false;
}
}  // namespace cz::lastaapps::vimxel::vim
