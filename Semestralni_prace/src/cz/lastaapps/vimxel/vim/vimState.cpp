#include "vimState.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {

VimState::VimState(
    shared_ptr<display::State> displayState,
    shared_ptr<table::Table> table,
    const fs::path& fileName)
    : mDisplayState(displayState),
      mTable(table),
      mFilename(fileName) {}

ParserResult VimState::setError(const string& message, const Mode next, Mode& outMode) {
	mReturnMode = next;
	mErrorMsg = message;
	outMode = Mode::ERROR;
	return ParserResult::ERROR;
}
}  // namespace cz::lastaapps::vimxel::vim
