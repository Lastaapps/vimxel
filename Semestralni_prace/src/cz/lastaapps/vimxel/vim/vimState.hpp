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

/**
 * @brief Represents VimParser internal state
 * is shared with individual parsers
 */
struct VimState {
	// data sources
	shared_ptr<display::State> mDisplayState;
	shared_ptr<table::Table> mTable;
	// file from the program has read lastly
	fs::path mFilename;
	// local clipboard
	string mClipboard;

	// currently selected position, cached
	table::Coordinates mPos;
	// current viewport, cached
	table::Coordinates mViewPort;
	// latest error message
	string mErrorMsg;
	// if an error occurred, there is stored the mode to go back after user reads the error
	Mode mReturnMode;

	/**
	 * @brief Construct a new Vim State object
	 *
	 * @param displayState shared display state to update
	 * @param table data source
	 * @param filename initial filename
	 */
	VimState(
	    shared_ptr<display::State> displayState,
	    shared_ptr<table::Table> table,
	    const fs::path& filename);

	/**
	 * @brief Sets state into error mode
	 * just a shortcut, so three lines of code don't have to be repeated all over the place
	 *
	 * @param message error message
	 * @param next the mode to switch to after data fetch
	 * @param outMode is changed to Mode::ERROR
	 * @return always ParserResult::ERROR
	 */
	ParserResult setError(const string& message, const Mode next, Mode& outMode);
};
}  // namespace cz::lastaapps::vimxel::vim

#endif