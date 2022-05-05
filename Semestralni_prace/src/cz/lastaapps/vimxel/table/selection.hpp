#ifndef H_SELECTION
#define H_SELECTION
#include <functional>
#include "coordinate.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::table {
class Selection final {
    Coordinates mFrom;
    Coordinates mTo;
    public:
    Selection(const Coordinates& from, const Coordinates& to);
    const Coordinates& from() const;
    const Coordinates& to() const;
    void iterateOver(function<void(const Coordinates&)> callback) const;
};
} // namespace cz::lastaapps::vimxel::table


#endif