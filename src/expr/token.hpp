#ifndef H_TOKEN
#define H_TOKEN
#include <string>

#include "../table/coordinate.hpp"
#include "../table/selection.hpp"
#include "token.hpp"
#include "tokenType.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {

using TT = TokenType;

/**
 * @brief Represents token parsed in Tokenizer
 * Subclasses may have additional payload
 */
struct Token {
	/**
	 * @brief Type of the token
	 */
	TT type;
	/**
	 * @brief Construct a new Token object
	 *
	 * @param t token type of this token
	 */
	Token(TT t) : type(t) {}
	virtual ~Token() = default;
};

/**
 * @brief Token with double payload
 */
struct DoubleToken final : public Token {
	// parsed number
	long double payload;
	DoubleToken(long double p) : Token(TT::DOUBLE), payload(p) {}
};

/**
 * @brief Token with string payload
 */
struct TextToken final : public Token {
	// parsed string
	string payload;
	TextToken(const string& p) : Token(TT::TEXT), payload(p) {}
};

/**
 * @brief Token representing cell
 */
struct CellToken final : public Token {
	// parsed cell coordinates
	table::Coordinates payload;
	CellToken(const table::Coordinates& p) : Token(TT::CELL), payload(p) {}
};

/**
 * @brief Token representing area selection
 */
struct SelectionToken final : public Token {
	// parsed selection
	table::Selection payload;
	SelectionToken(const table::Selection& p) : Token(TT::SELECTION), payload(p) {}
};
}  // namespace cz::lastaapps::vimxel::expr

#endif