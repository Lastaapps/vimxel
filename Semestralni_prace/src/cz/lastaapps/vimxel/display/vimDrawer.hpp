#ifndef H_VIM_DRAWER
#define H_VIM_DRAWER
#include <ncurses.h>
#include "drawer.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::display {
class VimDrawer : public Drawer {
    private:
    string mMode;
    string mCommand;
    string mCellContent;

    public:
    VimDrawer(WINDOW * w) : Drawer(w) {}
};
}

#endif