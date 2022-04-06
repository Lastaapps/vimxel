#include "coordinate.hpp"

#include <stdexcept>
#include <string>
using namespace std;

namespace cz::lastaapps::vimxel::table {
// --- Coordinates ------------------------------------------------------------
Coordinates::Coordinates(size_t x, size_t y)
    : mX(x), mY(y) {}
Coordinates::Coordinates(const string& x, size_t y)
    : Coordinates(fromString(x), y) {}
size_t Coordinates::x() const { return mX; }
size_t Coordinates::y() const { return mY; }
const string Coordinates::xString() const {
	return toString(mX);
}
bool Coordinates::operator==(const Coordinates& other) const {
	return mX == other.mX && mY == other.mY;
}
bool Coordinates::operator<(const Coordinates& other) const {
	if (mX < other.mX) return true;
	if (mX > other.mX) return false;
	return mY < other.mY;
}
size_t Coordinates::fromString(const string& str) {
	const size_t len = str.size();
	if (len == 0) throw invalid_argument("Empty string not acceptable!");
	size_t position = 0;
	size_t toAdd = pow(aToZ, len - 1);
	for (size_t i = 0; i < len; i++) {
		const uint8_t c = str[i];
		if (c < 'A' || 'Z' < c) throw invalid_argument("Invalid character padded: " + c);
		position += (c - 'A' + 1) * toAdd;
		toAdd /= aToZ;
	}
	return position;
}
string Coordinates::toString(size_t pos) {
	string s = "";
	while (pos > 0) {
		s += (uint8_t)('A' + pos % aToZ);
		pos /= aToZ;
	}
	s.reserve();
	return s;
}
size_t Coordinates::pow(size_t a, size_t x) {
	size_t toReturn = 0;
	if (x == 0) return 1;
	for (size_t i = 1; i <= x; i <<= 1) {
		if (x & i)
			toReturn += a;
		a *= a;
	}
	return toReturn;
}

}  // namespace cz::lastaapps::vimxel::table