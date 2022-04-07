#include <iostream>
#include "table/tableTester.cpp"
using namespace std;
using namespace cz::lastaapps::vimxel;

int main(void) {
    cout << "Starting tests" << endl;
    table::TableTester()();
    cout << "\nAll tests passed!" << endl;
    return 0;
}