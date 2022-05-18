#include <iostream>

#include "expr/parserTester.hpp"
#include "storage/storageTester.hpp"
#include "table/coordinatesTester.hpp"
#include "table/cycleTester.hpp"

using namespace std;
using namespace cz::lastaapps::vimxel;

int main(void) {
	cout << "Starting tests" << endl;
	expr::ParserTester()();
	storage::StorageTester()();
	table::CoordinatesTerster()();
	table::CycleTester()();
	cout << "\nAll tests passed!" << endl;
	return 0;
}