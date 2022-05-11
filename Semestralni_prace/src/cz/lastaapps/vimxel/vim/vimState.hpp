#ifndef H_VIM_STATE
#define H_VIM_STATE
#include <filesystem>
#include <memory>

#include "../display/state.hpp"
#include "../table/table.hpp"
#include "mode.hpp"
#include "parserResult.hpp"

using namespace std;
namespace fs = std::filesystem;

namespace cz::lastaapps::vimxel::vim {
struct VimState {
	shared_ptr<display::State> mDisplayState;
	shared_ptr<table::Table> mTable;
	fs::path mFilename;

	table::Coordinates mPos;
	table::Coordinates mViewPort;
	string mErrorMsg;
	Mode mReturnMode;

	VimState(
	    shared_ptr<display::State> displayState,
	    shared_ptr<table::Table> table,
	    const fs::path& filename);

	ParserResult setError(const string& message, const Mode next, Mode& outMode);
};
}  // namespace cz::lastaapps::vimxel::vim

#endif