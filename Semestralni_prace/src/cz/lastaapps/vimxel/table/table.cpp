#include "table.hpp"
#include "cell.hpp"

#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <string>


namespace cz::lastaapps::vimxel::table {


// --- Table ------------------------------------------------------------------
const Cell& Table::getCell(const Coordinates& coord) const {
	const auto iter = mMap.find(coord);
	if (iter == mMap.end())
		return emptyCell;
	return *(iter->second);
}
void Table::updateCell(const Coordinates& coord, const Cell& cell) {
	if (dynamic_cast<const EmptyCell*>(&cell) != nullptr)
		// delete
		mMap.erase(coord);
	else
		// insert/update
		mMap.insert_or_assign(coord, unique_ptr<const Cell>(&cell));
}
inline void Table::deleteCell(const Coordinates& coord) {
	updateCell(coord, emptyCell);
}

}  // namespace cz::lastaapps::vimxel::table