#ifndef COORDINATE_H
#define COORDINATE_H
#include <string>

using namespace std;
namespace cz::lastaapps::vimxel::table {

class Coordinates final {
   private:
	size_t mX, mY;

   public:
	Coordinates(size_t x, size_t y);
	Coordinates(const string& x, size_t y);
	bool operator==(const Coordinates& other) const;
	bool operator<(const Coordinates& other) const;
	size_t x() const;
	size_t y() const;
	const string xString() const;
	static size_t fromString(const string& str);
	static string toString(size_t pos);

   private:
	static constexpr uint8_t aToZ = 'Z' - 'A' + 1;
	static size_t pow(size_t a, size_t x);
};

}  // namespace cz::lastaapps::vimxel::table
#endif