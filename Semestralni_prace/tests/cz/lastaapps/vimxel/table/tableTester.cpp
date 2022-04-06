#include <iostream>

#include "../../../../../src/cz/lastaapps/vimxel/table/coordinate.hpp"
using namespace std;

namespace cz::lastaapps::vimxel::table {
class TableTester {
   public:
	void operator()() {
		testCoordinates();
	}

   private:
	void testCoordinates() {
        cout << "Testing coordinates" << endl;
	}
};
}  // namespace cz::lastaapps::vimxel::table