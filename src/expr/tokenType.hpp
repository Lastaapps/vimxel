#ifndef H_TOKEN_TYPE
#define H_TOKEN_TYPE

using namespace std;
namespace cz::lastaapps::vimxel::expr {

/**
 * @brief Represents all the possible types in expressions
 */
enum class TokenType {
    NONE, COMMA,
    // prior 0
    PLUS, MINUS,
    // prior 1
    TIMES, DIVIDE, MODULO,
    // prior 2
    // terms
    DOUBLE, TEXT, CELL, SELECTION,
    // brackets
    BRACKET_LS, BRACKET_RS, // ()
    BRACKET_LM, BRACKET_RM, // []
    BRACKET_LL, BRACKET_RL, // {}
    // constants
    PI, E, LIGHT_SPEED, GOLDEN_RATION,
    // functions
    POW, SQRT, ABS, EXP, LN, LOG2, LOG10, LOG,
    ROUND, CEIL, FLOOR, TRUNC,
    SIN, COS, TAN, COT, ARCSIN, ARCCOS, ARCTAN, ARCCOT,
    SUM, MAX, MIN, AVG,
    CONCAT, LOWER, UPPER,
};
} // namespace cz::lastaapps::vimxel:expr

#endif