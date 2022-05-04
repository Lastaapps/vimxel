#ifndef TABLE_H
#define TABLE_H
#include <map>
#include <memory>

#include "cell.hpp"
#include "coordinate.hpp"
#include "cellContract.hpp"
using namespace std;
namespace cz::lastaapps::vimxel::table {

class Table final {
   private:
	map<Coordinates, unique_ptr<const Cell>> mMap;
	EmptyCell emptyCell;
	vector<shared_ptr<CellContract>> mContracts;

   public:
	Table() = default;
	Table(const Table& other) = delete;
	Table(const Table&& other) = delete;
	Table& operator=(const Table& other) = delete;
	const Cell& getCell(const Coordinates& coord) const;
	void updateCell(const Coordinates& coord, const Cell& cell);
	void deleteCell(const Coordinates& coord);
	shared_ptr<CellContract> createCellContract();
	Coordinates tableSize() const;
	bool isEmpty() const;

   private:
	void updateContracts(const Coordinates& coord);
};
}  // namespace cz::lastaapps::vimxel::table
#endif
