#ifndef APP_H
#define APP_H
#include <vector>
#include <string>
#include "display/display.hpp"

using namespace std;
namespace cz::lastaapps::vimxel {

class App final {
    public:
    int run(vector<string> args);
    private:
    // Storage engine
    // NCurses Init
    // Table
    // Display
    // Vim
};


}  // namespace cz::lastaapps::vimxel

#endif