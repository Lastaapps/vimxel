#ifndef H_VIM_DRAWER
#define H_VIM_DRAWER
#include <ncurses.h>
#include <memory>
#include "drawer.hpp"
#include "../vim/vimContract.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::display {
class VimDrawer : public Drawer {
    private:
    shared_ptr<vim::VimContract> mContract;
    vim::VimInfo mInfo;

    public:
    VimDrawer(WINDOW * w, shared_ptr<vim::VimContract> contract);
    void draw() override;
	void selectPos(
	    const table::Coordinates& pos,
	    const table::Coordinates& viewPort) override;

    private:
    void updateInfo(const vim::VimInfo& info);
};
}

#endif