#include "cycleTester.hpp"

using namespace std;
using namespace cz::lastaapps::vimxel;

namespace cz::lastaapps::vimxel::table {

#define C(x, y) Coordinates((x), (y))

void CycleTester ::operator()() {
	cout << "Testing cycles" << endl;
	insertComplexCycle();
	insertSelfCycle();
}
void CycleTester ::insertComplexCycle() {
	Table t;
	assert(t.updateCell(C("A", 1), "=B1").success == true);
	assert(t.updateCell(C("B", 1), "=B2").success == true);
	assert(t.updateCell(C("B", 2), "=A2").success == true);
	assert(t.updateCell(C("A", 2), "=A1").success == false);
}
void CycleTester ::insertSelfCycle() {
	Table t;
	assert(t.updateCell(C("A", 1), "=A1").success == false);
}

}  // namespace cz::lastaapps::vimxel::table