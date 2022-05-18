#ifndef H_SELECTION
#define H_SELECTION
#include <functional>

#include "coordinate.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::table {

/**
 * @brief Represents area in table
 */
class Selection final {
	// lower position
	Coordinates mFrom;
	// greater position
	Coordinates mTo;

   public:
	/**
	 * @brief Construct a new Selection object
	 *
	 * @param from one position, may be returned by from() or to()
	 * @param to the other position, may be returned by from() or to()
	 */
	Selection(const Coordinates& from, const Coordinates& to);
	/**
	 * @brief Returns lower position according to coordinates < operator
	 *
	 * @return lower position
	 */
	const Coordinates& from() const;
	/**
	 * @brief Returns greater position according to coordinates < operator
	 *
	 * @return greater position
	 */
	const Coordinates& to() const;
	/**
	 * @brief Iterates over all the cells in area in undefined order
	 *
	 * @param callback function to call on each coordinate
	 */
	void iterateOver(function<void(const Coordinates&)> callback) const;
};
}  // namespace cz::lastaapps::vimxel::table

#endif