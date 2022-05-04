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
	string mFilename;

	table::Coordinates mPos;
	table::Coordinates mViewPort;
	string mErrorMsg;

	VimState(
	    shared_ptr<display::State> displayState,
	    shared_ptr<table::Table> table,
	    const string& filename);
};
}  // namespace cz::lastaapps::vimxel::vim

#endif