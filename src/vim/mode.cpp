#include "mode.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {
string to_string(Mode m) {
	switch (m) {
	case Mode::NONE:
		return "";
	case Mode::NORMAL:
		return "NORMAL";
	case Mode::INSERT:
		return "INSERT";
	case Mode::COMMAND:
		return "COMMAND";
	case Mode::ERROR:
		return "ERROR";
	}
	throw invalid_argument("Unknown Vim Mode");
}
}