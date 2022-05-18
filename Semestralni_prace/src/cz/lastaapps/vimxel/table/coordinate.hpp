#ifndef H_COORDINATE
#define H_COORDINATE
#include <functional>
#include <iostream>
#include <string>

using namespace std;
namespace cz::lastaapps::vimxel::table {

class Coordinates final {
   private:
	// local read coordinates
	size_t mX, mY;

   public:
	/**
	 * @brief Construct a new Coordinates object with x = 0 and y = 0
	 */
	Coordinates();
	/**
	 * @brief Copies coordinates from other source
	 *
	 * @param src coordinates to copy data from
	 */
	Coordinates(const Coordinates& src);
	/**
	 * @brief Moves coordinates from other source
	 *
	 * @param src coordinates to move data from
	 */
	Coordinates(Coordinates&& src);
	/**
	 * @brief Construct a new Coordinates object
	 * 
	 * @param x x coordinate
	 * @param y y coordinate
	 */
	Coordinates(size_t x, size_t y);
	/**
	 * @brief Construct a new Coordinates from human redable input
	 * so A1 is convertied to x = 0 a y = 0
	 * 
	 * @param x column name, letters A - Z
	 * @param y row number, 1 =<
	 */
	Coordinates(const string& x, size_t y);
	~Coordinates();
	Coordinates& operator=(Coordinates src);

/**
 * @brief Checks if two coordinates are the same
 * 
 * @param other other coordinate to check
 * @return true if they are same
 */
	bool operator==(const Coordinates& other) const;
/**
 * @brief Checks if two coordinates are not the same
 * 
 * @param other other coordinate to check
 * @return true if they are not same
 */
	bool operator!=(const Coordinates& other) const;
	/**
	 * @brief Compares x firstly, y secondly
	 * 
	 * @param other other coodinate to check
	 * @return true if other is greater
	 */
	bool operator<(const Coordinates& other) const;

	/**
	 * @brief Sums two coordinates
	 * 
	 * @param other other coordinate to add
	 * @return coodrinate with [x1 + x2, y1 + y2]
	 */
	Coordinates operator+(const Coordinates& other) const;
	/**
	 * @brief Diff of two coordinates
	 * 
	 * @param other other coordinate to subtract
	 * @return coodrinate with [x1 - x2, y1 - y2]
	 */
	Coordinates operator-(const Coordinates& other) const;

/**
 * @brief Gets x coordinate
 * 
 * @return x coordinate 
 */
	size_t x() const;
/**
 * @brief Gets y coordinate
 * 
 * @return y coordinate 
 */
	size_t y() const;
	/**
	 * @brief Converts x coordinate into string form for users
	 * 
	 * @return x in human form, like A, BZ
	 */
	const string xString() const;

/**
 * @brief Creates copy with same y, but new x
 * 
 * @param val new x
 * @return new coordinates 
 */
	Coordinates withX(const size_t val = 0) const;
/**
 * @brief Creates copy with same x, but new y
 * 
 * @param val new y
 * @return new coordinates 
 */
	Coordinates withY(const size_t val = 0) const;
	/**
	 * @brief Create new coordinate with x increased by an amounts
	 * 
	 * @param by the amount of change
	 * @return new Coordinates
	 */
	Coordinates incX(const size_t by = 1) const;
	/**
	 * @brief Create new coordinate with y increased by an amounts
	 * 
	 * @param by the amount of change
	 * @return new Coordinates
	 */
	Coordinates incY(const size_t by = 1) const;
	/**
	 * @brief Create new coordinate with x decreased by an amounts
	 * 
	 * @param by the amount of change
	 * @return new Coordinates
	 */
	Coordinates decX(const size_t by = 1) const;
	/**
	 * @brief Create new coordinate with y decreased by an amounts
	 * 
	 * @param by the amount of change
	 * @return new Coordinates
	 */
	Coordinates decY(const size_t by = 1) const;

   private:
   // the length of alphabet
	static constexpr uint8_t aToZ = 'Z' - 'A' + 1;
	/**
	 * @brief Parses coodrinate from human representation
	 * 
	 * @param str string to parse
	 * @return coordinate
	 */
	static size_t fromString(const string& str);
	/**
	 * @brief Converts coordinate into human redable form
	 * 
	 * @param pos coordinate to convert to human redable form
	 * @return human representation 
	 */
	static string toString(size_t pos);
	/**
	 * @brief Just pow, no more
	 * 
	 * @param a base
	 * @param x exponent
	 * @return a^x
	 */
	static size_t pow(size_t a, size_t x);
};

/**
 * @brief Prints coordinate into stream in "[x, y]" format
 * 
 * @param out stream to print into
 * @param c coordinate to print
 * @return the same stream passed as out parameter
 */
ostream& operator<<(ostream& out, const Coordinates& c);

}  // namespace cz::lastaapps::vimxel::table

/**
 * @brief Defalt hash function for Coordinates
 * in meaningfull range there should be no colissions at all
 */
template <>
struct std::hash<cz::lastaapps::vimxel::table::Coordinates> {
	std::size_t operator()(const cz::lastaapps::vimxel::table::Coordinates& coord) const noexcept {
		return coord.x() + (coord.y() << (sizeof(size_t) * 8 / 2));
	}
};
#endif