#include "vimState.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {

VimState::VimState(
    shared_ptr<display::State> displayState,
    shared_ptr<table::Table> table,
    vector<string> args)
    : mDisplayState(displayState),
      mTable(table),
      mArgs(args) {}
}  // namespace cz::lastaapps::vimxel::vim
