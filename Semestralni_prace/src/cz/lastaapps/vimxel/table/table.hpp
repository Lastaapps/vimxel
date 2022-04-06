#ifndef TABLE_H
#define TABLE_H
#include <map>
#include <memory>

#include "cell.hpp"
#include "coordinate.hpp"
using namespace std;
namespace cz::lastaapps::vimxel::table {

class Table final {
   private:
	map<Coordinates, unique_ptr<const Cell>> mMap;
	EmptyCell emptyCell;

   public:
	Table(const Table& other) = delete;
	Table(const Table&& other) = delete;
	Table& operator=(const Table& other) = delete;
	const Cell& getCell(const Coordinates& coord) const;
	void updateCell(const Coordinates& coord, const Cell& cell);
	void deleteCell(const Coordinates& coord);
};
}  // namespace cz::lastaapps::vimxel::table
#endif
