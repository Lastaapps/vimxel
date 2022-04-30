#ifndef APP_H
#define APP_H
#include <ncurses.h>
#include <vector>
#include <string>
#include "display/display.hpp"
#include "table/table.hpp"

using namespace std;
namespace cz::lastaapps::vimxel {

class App final {
    public:
    int run(vector<string> args);
    private:
    
    shared_ptr<table::Table> loadTable();
    void initNCurses();
    void destroyNCurses();
    void setupDisplay();

    // Storage engine
    // Vim
};


}  // namespace cz::lastaapps::vimxel

#endif