#ifndef H_TOKENIZER
#define H_TOKENIZER
#include <string>
#include <memory>
#include <set>
#include "token.hpp"
#include "tokenType.hpp"
#include "../table/coordinate.hpp"
#include "../table/selection.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using TT = TokenType;
using ST = shared_ptr<Token>;
class Tokenizer final {
    using SItr = string::const_iterator;
    string mString;
    SItr mPos;

    set<table::Coordinates> mDependent;

    public:
    Tokenizer(const string& string);
    ST nextToken();
    const set<table::Coordinates>& getDependent() const;
    private:
    bool parseOperators(Token* & out);
    bool parseNumber(Token* & out);
    /**
     * Doesn't support escaping " or ' chars. But average user
     * doesn't know about this option anyway and will use CONCAT
     */
    bool parseText(Token* & out);
    bool parseCell(Token* & out);
    bool parseFun(Token* & out);
    void skipSpaces();

    void updateDepend(const table::Coordinates& coord);
    void updateDepend(const table::Selection& sel);
};
} // namespace cz::lastaapps::vimxel:expr

#endif