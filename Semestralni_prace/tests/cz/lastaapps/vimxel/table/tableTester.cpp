#include <cassert>
#include <iostream>

#include "../../../../../src/cz/lastaapps/vimxel/table/coordinate.hpp"
#include "../testUtils.cpp"
using namespace std;
using namespace cz::lastaapps::vimxel;

namespace cz::lastaapps::vimxel::table {
class TableTester {
   public:
	void operator()() {
		testCoordinates();
	}

   private:
	void testCoordinates() {
		cout << "Testing coordinates" << endl;

		cout << (Coordinates(0, "BEH").y() + 1) << endl;

		assPr(Coordinates(0, "A").y(), 0Lu);
		assPr(Coordinates(0, "B").y(), 1Lu);
		assPr(Coordinates(0, "Z").y(), 25Lu);
		assPr(Coordinates(0, "AA").y(), 26Lu);
		assPr(Coordinates(0, "AB").y(), 27Lu);
		assPr(Coordinates(0, "BA").y(), 52Lu);
		assPr(Coordinates(0, "ZZ").y(), 701Lu);
		assPr(Coordinates(0, "AAA").y(), 702Lu);
		assPr(Coordinates(0, "AAB").y(), 703Lu);
		assPr(Coordinates(0, "ABA").y(), 728Lu);
		assPr(Coordinates(0, "AMJ").y(), 1023Lu);

		assPr(Coordinates(0, "A").yString(), "A"s);
		assPr(Coordinates(0, "B").yString(), "B"s);
		assPr(Coordinates(0, "Z").yString(), "Z"s);
		assPr(Coordinates(0, "AA").yString(), "AA"s);
		assPr(Coordinates(0, "AB").yString(), "AB"s);
		assPr(Coordinates(0, "ZZ").yString(), "ZZ"s);
		assPr(Coordinates(0, "AAA").yString(), "AAA"s);
		assPr(Coordinates(0, "ABA").yString(), "ABA"s);
		assPr(Coordinates(0, "BBA").yString(), "BBA"s);
		assPr(Coordinates(0, "AMJ").yString(), "AMJ"s);
		assPr(Coordinates(0, "BMJ").yString(), "BMJ"s);

		{ // Test str to int conversion
			size_t i = 0;
			for (string str = "A"s; str.size() <= 4; str = incStr(str)) {
				const Coordinates coord = Coordinates(0, str);
				assPrMsg(str, i, coord.y());
				i++;
			}
		}
		{ // Test str to int and back conversion
			for (string str = "A"s; str.size() <= 4; str = incStr(str)) {
				const Coordinates coord = Coordinates(0, str);
				assPrMsg(to_string(coord.y() + 1), coord.yString(), str);
			}
		}
	}

	string incStr(string str) {
		for (size_t i = str.size(); i > 0; i--) {
			uint8_t c = str.at(i - 1);
			if (c != 'Z') {
				str.at(i - 1) = c + 1;
				return str;
			} else {
				str.at(i - 1) = 'A';
			}
		}
		str = 'A' + str;
		return str;
	}
};

}  // namespace cz::lastaapps::vimxel::table