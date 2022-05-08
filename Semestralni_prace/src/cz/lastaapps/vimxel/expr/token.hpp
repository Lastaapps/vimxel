#ifndef H_TOKEN
#define H_TOKEN
#include <string>
#include "token.hpp"
#include "tokenType.hpp"
#include "../table/coordinate.hpp"
#include "../table/selection.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using TT = TokenType;

struct Token {
    TT type;
    Token(TT t) : type(t) {}
    virtual ~Token() = default;
};
struct DoubleToken final : public Token {
    long double payload;
    DoubleToken(long double p) : Token(TT::DOUBLE), payload(p) {}
};
struct TextToken final : public Token {
    string payload;
    TextToken(const string& p) : Token(TT::TEXT), payload(p) {}
};
struct CellToken final : public Token {
    table::Coordinates payload;
    CellToken(const table::Coordinates& p) : Token(TT::CELL), payload(p) {}
};
struct SelectionToken final : public Token {
    table::Selection payload;
    SelectionToken(const table::Selection& p) : Token(TT::SELECTION), payload(p) {}
};
} // namespace cz::lastaapps::vimxel:expr

#endif