#ifndef H_VIM_STATE
#define H_VIM_STATE
#include <memory>

#include "../display/state.hpp"
#include "../table/table.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {
struct VimState {
	shared_ptr<display::State> mDisplayState;
	shared_ptr<table::Table> mTable;
	const vector<string> mArgs;
	table::Coordinates mPos;
	table::Coordinates mViewPort;
	VimState(
	    shared_ptr<display::State> displayState,
	    shared_ptr<table::Table> table,
	    vector<string> args);
};
}  // namespace cz::lastaapps::vimxel::vim

#endif