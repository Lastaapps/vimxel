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
    DOUBLE, TEXT, CELL, SELECTION,
    BRACKET_LS, BRACKER_RS, // ()
    BRACKET_LM, BRACKER_RM, // []
    BRACKET_LL, BRACKER_RL, // {}
    // functions
    SQRT, POW, ABS, E, LOG,
    ROUND, CEIL, FLOOR, TAIL,
    SIN, COS, TAN, COT, ARCSIN, ARCCOS, ARCTAN, ARCCTG,
    SUM, MAX, MIN, AVG,
    CONCAT,
};
} // namespace cz::lastaapps::vimxel:expr

#endif