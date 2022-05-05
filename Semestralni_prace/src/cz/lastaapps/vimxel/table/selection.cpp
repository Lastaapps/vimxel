#include "selection.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::table {
    Selection::Selection(const Coordinates& from, const Coordinates& to)
    : mFrom(from < to ? from : to), mTo(to < from ? from : to) {}
    const Coordinates& Selection::from() const { return mFrom; }
    const Coordinates& Selection::to() const{ return mTo; }
    void Selection::iterateOver(function<void(const Coordinates&)> callback) const {
	    for (size_t y = mFrom.y(); y <= mTo.y(); y++)
		    for (size_t x = mFrom.x(); x <= mTo.x(); x++)
			    callback(Coordinates(x, y));
    }
} // namespace cz::lastaapps::vimxel::table