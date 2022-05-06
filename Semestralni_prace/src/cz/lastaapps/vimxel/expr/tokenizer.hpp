#ifndef H_TOKENIZER
#define H_TOKENIZER
#include <string>
#include <memory>
#include <set>
#include <map>
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

    map<string, TT> mFunMapper {
        {"sqrt"s, TT::SQRT}, {"pow"s, TT::POW},
        {"abs"s, TT::ABS}, {"e"s, TT::E},
        {"ln"s, TT::LN}, {"log2"s, TT::LOG2}, {"log10"s, TT::LOG10},

        {"round"s, TT::ROUND}, {"ceil"s, TT::CEIL}, {"floor"s, TT::FLOOR}, {"tail"s, TT::TAIL},

        {"sin"s, TT::SIN}, {"cos"s, TT::COS}, {"tan"s, TT::TAN}, {"cot"s, TT::COT},
        {"arcsin"s, TT::ARCSIN}, {"arccos"s, TT::ARCCOS}, {"arctan"s, TT::ARCTAN}, {"arccot"s, TT::ARCCOT},

        {"sum"s, TT::SUM}, {"max"s, TT::MAX}, {"min"s, TT::MIN}, {"avg"s, TT::AVG},

        {"concat"s, TT::CONCAT},
        //{""s, TT::},
    };
};
} // namespace cz::lastaapps::vimxel:expr

#endif