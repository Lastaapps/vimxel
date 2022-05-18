#ifndef H_CELL_CONTRACT
#define H_CELL_CONTRACT
#include <functional>
#include <list>

#include "coordinate.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::table {

/**
 * @brief Contract providing data from table to other app modules
 */
class CellContract {
	using Callback = function<void(const Coordinates&)>;
	// callback to call
	Callback mCallback;

   public:
	virtual ~CellContract() = default;

	/**
	 * @brief Gets the content of the cell at coord from data source
	 *
	 * @param coord the position of the cell
	 * @return cell content
	 */
	virtual string getDataAt(const Coordinates& coord) const = 0;
	/**
	 * @brief called by data provider, notifies observers
	 *
	 * @param coord cell position
	 */
	void dataUpdatedAt(const Coordinates& coord);
	/**
	 * @brief Register a callback, the old one is overwritten
	 */
	void registerCallback(Callback);
	/**
	 * @brief unregisters callback
	 */
	void unregisterCallback();
};
}  // namespace cz::lastaapps::vimxel::table
#endif