#ifndef H_CELL_CONTRACT
#define H_CELL_CONTRACT
#include "coordinate.hpp"
#include <functional>
#include <list>

using namespace std;
namespace cz::lastaapps::vimxel::table {
class CellContract {
	using Callback = function<void(const Coordinates&)>;
	Callback mCallback;
    public:
    virtual ~CellContract() {};
    virtual string getDataAt(const Coordinates & coord) const = 0;
    void dataUpdatedAt(const Coordinates & coord);
    void registerCallback(Callback);
    void unregisterCallback();
};
}
#endif