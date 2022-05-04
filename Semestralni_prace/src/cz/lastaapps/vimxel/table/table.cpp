#include "table.hpp"

#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <string>

#include "../log.hpp"
#include "cell.hpp"

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
		mMap.insert_or_assign(coord, unique_ptr<const Cell>(cell.clone()));

	updateContracts(coord);
	mChanged = true;
}
inline void Table::deleteCell(const Coordinates& coord) {
	updateCell(coord, emptyCell);
}
shared_ptr<CellContract> Table::createCellContract() {
	class TableCellContract final : public CellContract {
		const Table& mT;

	   public:
		TableCellContract(const Table& t) : mT(t) {}
		string getDataAt(const Coordinates& coord) const override {
			return mT.getCell(coord).getContent();
		}
	};
	auto ptr = shared_ptr<CellContract>(dynamic_cast<CellContract*>(new TableCellContract(*this)));
	mContracts.push_back(ptr);
	return ptr;
}
void Table::updateContracts(const Coordinates& coord) {
	mlog << "Updating data at " << coord << endl;
	for (size_t i = 0; i < mContracts.size(); i++) {
		auto ptr = mContracts[i];
		if (ptr.use_count() <= 1) {
			mContracts.erase(mContracts.begin() + i);
			i--;
		} else {
			ptr->dataUpdatedAt(coord);
		}
	}
}
Coordinates Table::tableSize() const {
	size_t maxX = 0, maxY = 0;
	for (const auto& [key, value] : mMap) {
		if (key.x() > maxX) maxX = key.x();
		if (key.y() > maxY) maxY = key.y();
	}
	return Coordinates(maxX + 1, maxY + 1);  // to convert coordinates to size
}
bool Table::isEmpty() const {
	return mMap.empty();
}
void Table::eraseAll() {
	mMap.erase(mMap.begin(), mMap.end());
	mChanged = true;
}
bool Table::changed() const {
	return mChanged;
}
void Table::clearChanged() {
	mChanged = false;
}

}  // namespace cz::lastaapps::vimxel::table