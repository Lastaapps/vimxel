#include "coordinatesTester.hpp"

using namespace std;
using namespace cz::lastaapps::vimxel;

namespace cz::lastaapps::vimxel::table {

void CoordinatesTerster::operator()() {
	testCoordinates();
}

void CoordinatesTerster ::testCoordinates() {
	cout << "Testing coordinates" << endl;

	assPr(Coordinates("A", 0).x(), 0Lu);
	assPr(Coordinates("B", 0).x(), 1Lu);
	assPr(Coordinates("Z", 0).x(), 25Lu);
	assPr(Coordinates("AA", 0).x(), 26Lu);
	assPr(Coordinates("AB", 0).x(), 27Lu);
	assPr(Coordinates("BA", 0).x(), 52Lu);
	assPr(Coordinates("ZZ", 0).x(), 701Lu);
	assPr(Coordinates("AAA", 0).x(), 702Lu);
	assPr(Coordinates("AAB", 0).x(), 703Lu);
	assPr(Coordinates("ABA", 0).x(), 728Lu);
	assPr(Coordinates("AMJ", 0).x(), 1023Lu);

	assPr(Coordinates("A", 0).xString(), "A"s);
	assPr(Coordinates("B", 0).xString(), "B"s);
	assPr(Coordinates("Z", 0).xString(), "Z"s);
	assPr(Coordinates("AA", 0).xString(), "AA"s);
	assPr(Coordinates("AB", 0).xString(), "AB"s);
	assPr(Coordinates("ZZ", 0).xString(), "ZZ"s);
	assPr(Coordinates("AAA", 0).xString(), "AAA"s);
	assPr(Coordinates("ABA", 0).xString(), "ABA"s);
	assPr(Coordinates("BBA", 0).xString(), "BBA"s);
	assPr(Coordinates("AMJ", 0).xString(), "AMJ"s);
	assPr(Coordinates("BMJ", 0).xString(), "BMJ"s);

	{  // Test str to int conversion
		size_t i = 0;
		for (string str = "A"s; str.size() <= 4; str = incStr(str)) {
			const Coordinates coord = Coordinates(str, 0);
			assPrMsg(str, i, coord.x());
			i++;
		}
	}
	{  // Test str to int and back conversion
		for (string str = "A"s; str.size() <= 4; str = incStr(str)) {
			const Coordinates coord = Coordinates(str, 0);
			assPrMsg(to_string(coord.x() + 1), coord.xString(), str);
		}
	}
}

string CoordinatesTerster ::incStr(string str) {
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

}  // namespace cz::lastaapps::vimxel::table