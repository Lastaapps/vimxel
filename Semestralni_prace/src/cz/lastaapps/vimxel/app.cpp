#include "app.hpp"

namespace cz::lastaapps::vimxel {
    int App::run(vector<string> args) {
        display::Display().draw();
	    return 0;
    }
}