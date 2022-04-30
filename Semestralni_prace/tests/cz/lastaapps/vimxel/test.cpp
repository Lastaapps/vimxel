#include <iostream>
#include "table/tableTester.cpp"
#include "storage/storageTester.cpp"
using namespace std;
using namespace cz::lastaapps::vimxel;

int main(void) {
    cout << "Starting tests" << endl;
    table::TableTester()();
    storage::StorageTester()();
    cout << "\nAll tests passed!" << endl;
    return 0;
}