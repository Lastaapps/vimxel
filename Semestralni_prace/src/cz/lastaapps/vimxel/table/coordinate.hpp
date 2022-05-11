#ifndef H_COORDINATE
#define H_COORDINATE
#include <string>
#include <iostream>
#include <functional>

using namespace std;
namespace cz::lastaapps::vimxel::table {

class Coordinates final {
   private:
	size_t mX, mY;

   public:
	Coordinates();
	Coordinates(const Coordinates& src);
	Coordinates(Coordinates&& src);
	Coordinates(size_t x, size_t y);
	Coordinates(const string& x, size_t y);
	~Coordinates();
	Coordinates& operator=(Coordinates src);

	bool operator==(const Coordinates& other) const;
	bool operator!=(const Coordinates& other) const;
	bool operator<(const Coordinates& other) const;

	Coordinates operator + (const Coordinates& other) const;
	Coordinates operator - (const Coordinates& other) const;

	size_t x() const;
	size_t y() const;
	const string xString() const;

	Coordinates withX(const size_t val = 0) const;
	Coordinates withY(const size_t val = 0) const;
	Coordinates incX(const size_t by = 1) const;
	Coordinates incY(const size_t by = 1) const;
	Coordinates decX(const size_t by = 1) const;
	Coordinates decY(const size_t by = 1) const;

   private:
	static constexpr uint8_t aToZ = 'Z' - 'A' + 1;
	static size_t fromString(const string& str);
	static string toString(size_t pos);
	static size_t pow(size_t a, size_t x);
};

ostream& operator<<(ostream& out, const Coordinates& c);

}  // namespace cz::lastaapps::vimxel::table

template<>
struct std::hash<cz::lastaapps::vimxel::table::Coordinates> {
    std::size_t operator()(const cz::lastaapps::vimxel::table::Coordinates & coord) const noexcept {
		return coord.x() + (coord.y() << (sizeof(size_t) * 8 / 2));
	}
};
#endif