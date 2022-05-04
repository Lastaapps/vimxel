#include "vimState.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {

VimState::VimState(
    shared_ptr<display::State> displayState,
    shared_ptr<table::Table> table,
    const string& fileName)
    : mDisplayState(displayState),
      mTable(table),
      mFilename(fileName) {}
}  // namespace cz::lastaapps::vimxel::vim
