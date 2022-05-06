#ifndef H_TOKEN_TYPE
#define H_TOKEN_TYPE

using namespace std;
namespace cz::lastaapps::vimxel::expr {
enum class TokenType {
    NONE, COMMA,
    // prior 0
    PLUS, MINUS,
    // prior 1
    TIMES, DIVIDE,
    // prior 2
    // terms
    DOUBLE, TEXT, CELL, SELECTION,
    // brackets
    BRACKET_LS, BRACKER_RS, // ()
    BRACKET_LM, BRACKER_RM, // []
    BRACKET_LL, BRACKER_RL, // {}
    // functions
    POW, SQRT, ABS, E, LN, LOG2, LOG10,
    ROUND, CEIL, FLOOR, TAIL,
    SIN, COS, TAN, COT, ARCSIN, ARCCOS, ARCTAN, ARCCOT,
    SUM, MAX, MIN, AVG,
    CONCAT,
};
} // namespace cz::lastaapps::vimxel:expr

#endif