#ifndef H_PARSER
#define H_PARSER
#include <functional>
#include <memory>

#include "../table/coordinate.hpp"
#include "nodes/aggregateFunNodes.hpp"
#include "nodes/constantNodes.hpp"
#include "nodes/mathFunNodes.hpp"
#include "nodes/mathOperatorNodes.hpp"
#include "nodes/mathProcessNodes.hpp"
#include "nodes/node.hpp"
#include "nodes/termNode.hpp"
#include "nodes/terms.hpp"
#include "nodes/textManipNodes.hpp"
#include "nodes/trigonometryNodes.hpp"
#include "tokenizer.hpp"

using namespace std;
using namespace cz::lastaapps::vimxel::table;
namespace cz::lastaapps::vimxel::expr {

using STokenzizer = shared_ptr<Tokenizer>;
using SToken = shared_ptr<Token>;
using STerm = shared_ptr<Term>;
using SSingleTerm = shared_ptr<SingleTerm>;
using SNode = shared_ptr<Node>;
using TT = TokenType;

/****************************************
 * Expression evaulation grammar
 * E: E + T | T
 * T: T * T | F
 * F: C | (E) | max(E, ...) | -(F)
 *****************************************/
class Parser final {
	// provides tokens while parsing
	STokenzizer mTokenizer;
	// provides values for cell evaluation
	function<SSingleTerm(const table::Coordinates&)> mProvider;
	// current token
	SToken mToken;

   public:
	/**
	 * @brief Construct a new Parser object
	 *
	 * @param tokenizer token provider
	 * @param dataProvider provides cell values
	 */
	Parser(STokenzizer tokenizer, function<SSingleTerm(const table::Coordinates&)> dataProvider);

	/**
	 * @brief Reads whole tokenizer and creates Node tree, then evaluates it
	 *
	 * @return evaluation result
	 * @throw exception on invalid or empty expression
	 */
	STerm evaluate();

   private:
	/**
	 * @brief Updates mToken
	 */
	void nextToken();
	/**
	 * @brief Handles E - Expresion part of alphabet
	 *
	 * @return parsed Node
	 */
	SNode evE();
	/**
	 * @brief Handles T - Term part of alphabet
	 *
	 * @return parsed Node
	 */
	SNode evT();
	/**
	 * @brief Handles F - Factor part of alphabet
	 *
	 * @return parsed Node
	 */
	SNode evF();
	/**
	 * @brief Parses terms if matched
	 * @return true if anything was parsed
	 */
	bool evFTerms(SNode&);
	/**
	 * @brief Parses constants if matched
	 * @return true if anything was parsed
	 */
	bool evFConstants(SNode&);
	/**
	 * @brief Parses operators if matched
	 * @return true if anything was parsed
	 */
	bool evFOperators(SNode&);
	/**
	 * @brief Parses brackets if matched
	 * @return true if anything was parsed
	 */
	bool evFBrackets(SNode&);

	/**
	 * @brief Parses functions if matched
	 * @return true if anything was parsed
	 */
	bool evFFunctions(SNode&);
	/**
	 * @brief Check if result from evFFuncionsOperands
	 * returned valid result for this type of function
	 * if true, then constructs node
	 *
	 * @tparam type expected token
	 * @tparam size how many operands in expected, 0 for infinity
	 * @tparam Name Node to construct
	 * @return true if token type was matched
	 * @throw ivalid_argument if token type matches, but the number of arguments mismatches
	 */
	template <TT type, size_t size, typename Name>
	bool evFFunctionsCheck(SNode&);
	/**
	 * @brief Parses brackets and arts for a function in them
	 *
	 * @param type token type to match function
	 * @return true if token type matches
	 * @throw invalid_argument expresion doesn't respect right comma separation
	 */
	pair<bool, vector<SNode>> evFFunctionsOperands(const TT type);
};
}  // namespace cz::lastaapps::vimxel::expr

#endif