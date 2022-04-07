#include "coordinate.hpp"

#include <stdexcept>
#include <string>
using namespace std;

namespace cz::lastaapps::vimxel::table {
// --- Coordinates ------------------------------------------------------------
Coordinates::Coordinates(size_t x, size_t y)
    : mX(x), mY(y) {}
Coordinates::Coordinates(size_t x, const string& y)
    : Coordinates(x, fromString(y)) {}
size_t Coordinates::x() const { return mX; }
size_t Coordinates::y() const { return mY; }
const string Coordinates::yString() const {
	return toString(mY);
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
	return position - 1;
}
string Coordinates::toString(size_t pos) {
	string s = "";
	pos++;
	// computes modulos of aToZ
	// if the modulo is 0, aToZ needs to be subtracted
	while(pos != 0) {
		const size_t num = pos % aToZ;
		pos = (pos - (num == 0 ? aToZ : 0)) / aToZ;
		s += num != 0 ? 'A' - 1 + num : 'Z';
	}
	// reverse string
	const size_t len = s.length();
	for (size_t i = 0; i < len / 2; i++)
		std::swap(s[i], s[len - i - 1]);
	return s;
}
size_t Coordinates::pow(size_t a, size_t x) {
	size_t toReturn = 1;
	for (size_t i = 1; i <= x; i <<= 1) {
		if (x & i)
			toReturn *= a;
		a *= a;
	}
	return toReturn;
}

}  // namespace cz::lastaapps::vimxel::table