#ifndef H_MODE
#define H_MODE
#include <string>
#include <stdexcept>

using namespace std;
namespace cz::lastaapps::vimxel::vim {
enum class Mode {
    NONE,
    NORMAL,
    INSERT,
	COMMAND,
    ERROR,
};
string to_string(Mode m);
}

#endif