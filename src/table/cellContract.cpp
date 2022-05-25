#include "cellContract.hpp"

namespace cz::lastaapps::vimxel::table {
void CellContract::dataUpdatedAt(const Coordinates& coord) {
	mCallback(coord);
}
void CellContract::registerCallback(Callback c) {
	mCallback = c;
}
void CellContract::unregisterCallback() {
	mCallback = Callback();
}
}  // namespace cz::lastaapps::vimxel::table