#ifndef H_TOKENIZER
#define H_TOKENIZER
#include <map>
#include <memory>
#include <set>
#include <string>

#include "../table/coordinate.hpp"
#include "../table/selection.hpp"
#include "token.hpp"
#include "tokenType.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {

using SToken = shared_ptr<Token>;
using TT = TokenType;

/**
 * @brief Parses a string into individual tokens for future parsing in Parser
 */
class Tokenizer final {
	using SItr = string::const_iterator;
	// parsed text
	const string mString;
	// current parser position
	SItr mPos;

	// all the found cell dependencies of expression
	set<table::Coordinates> mDependent;

   public:
	/**
	 * @brief Construct a new Tokenizer object
	 *
	 * @param string text to tokenize
	 */
	Tokenizer(const string& string);

	/**
	 * @brief Parses next token
	 *
	 * @return next token
	 * @throw exception when parsing error happens
	 */
	SToken nextToken();
	/**
	 * @brief Goes through whole string and throws tokens away
	 * useful for getting just cell dependencies
	 * @throw exception when parsing error happens
	 */
	void skipAll();
	/**
	 * @brief Get all the cells this expression depends on
	 * must be called after nextToken() returned NONE, otherwise some dependencies na be missed
	 *
	 * @return cell dependencies
	 */
	const set<table::Coordinates>& getDependent() const;

   private:
	/**
	 * @brief Tryies to match operator
	 *
	 * @param out found token
	 * @return true if token was matched
	 */
	bool parseOperators(SToken& out);
	/**
	 * @brief Tryies to match number
	 *
	 * @param out found token
	 * @return true if token was matched
	 */
	bool parseNumber(SToken& out);
	/**
	 * @brief Tryies to match text in '' or ""
	 * Doesn't support escaping " or ' chars. But average user
	 * doesn't know about this option anyway and will use CONCAT
	 *
	 * @param out found token
	 * @return true if token was matched
	 */
	bool parseText(SToken& out);
	/**
	 * @brief Tryies to match cell or cell area
	 *
	 * @param out found token
	 * @return true if token was matched
	 */
	bool parseCell(SToken& out);
	/**
	 * @brief Tryies to match funcion
	 *
	 * @param out found token
	 * @return true if token was matched
	 */
	bool parseFun(SToken& out);
	/**
	 * @brief Moves mPos iterator until nonspace char or end is reached
	 */
	void skipSpaces();

	/**
	 * @brief Add cell to depend list
	 * @param coord cell to add
	 */
	void updateDepend(const table::Coordinates& coord);
	/**
	 * @brief Add every cell from area to depend list
	 * @param sel selection to add cells from
	 */
	void updateDepend(const table::Selection& sel);

	/**
	 * @brief All the function names, so they can be easily matched
	 */
	map<string, TT> mFunMapper{
	    {"pi"s, TT::PI}, {"e"s, TT::E}, {"c"s, TT::LIGHT_SPEED}, {"gr"s, TT::GOLDEN_RATION},

	    {"sqrt"s, TT::SQRT},
	    {"pow"s, TT::POW},
	    {"abs"s, TT::ABS},
	    {"exp"s, TT::EXP},
	    {"ln"s, TT::LN},
	    {"log2"s, TT::LOG2},
	    {"log10"s, TT::LOG10},
	    {"log"s, TT::LOG},

	    {"round"s, TT::ROUND},
	    {"ceil"s, TT::CEIL},
	    {"floor"s, TT::FLOOR},
	    {"trunc"s, TT::TRUNC},

	    {"sin"s, TT::SIN},
	    {"cos"s, TT::COS},
	    {"tan"s, TT::TAN},
	    {"cot"s, TT::COT},
	    {"asin"s, TT::ARCSIN},
	    {"acos"s, TT::ARCCOS},
	    {"atan"s, TT::ARCTAN},
	    {"acot"s, TT::ARCCOT},
	    {"arcsin"s, TT::ARCSIN},
	    {"arccos"s, TT::ARCCOS},
	    {"arctan"s, TT::ARCTAN},
	    {"arccot"s, TT::ARCCOT},

	    {"sum"s, TT::SUM},
	    {"max"s, TT::MAX},
	    {"min"s, TT::MIN},
	    {"avg"s, TT::AVG},

	    {"concat"s, TT::CONCAT},
	    {"lower"s, TT::LOWER},
	    {"upper"s, TT::UPPER},
	    //{""s, TT::},
	};
};
}  // namespace cz::lastaapps::vimxel::expr

#endif