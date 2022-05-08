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
using SToken = shared_ptr<Token>;
using TT = TokenType;

class Tokenizer final {
	using SItr = string::const_iterator;
    const string mString;
    SItr mPos;

    set<table::Coordinates> mDependent;

    public:
    Tokenizer(const string& string);
    SToken nextToken();
    void skipAll();
    const set<table::Coordinates>& getDependent() const;
    private:
    bool parseOperators(SToken & out);
    bool parseNumber(SToken & out);
    /**
     * Doesn't support escaping " or ' chars. But average user
     * doesn't know about this option anyway and will use CONCAT
     */
    bool parseText(SToken & out);
    bool parseCell(SToken & out);
    bool parseFun(SToken & out);
    void skipSpaces();

    void updateDepend(const table::Coordinates& coord);
    void updateDepend(const table::Selection& sel);

    map<string, TT> mFunMapper {
        {"pi"s, TT::PI}, {"e"s, TT::E}, {"c"s, TT::LIGHT_SPEED}, {"gr"s, TT::GOLDEN_RATION},

        {"sqrt"s, TT::SQRT}, {"pow"s, TT::POW},
        {"abs"s, TT::ABS}, {"exp"s, TT::EXP},
        {"ln"s, TT::LN}, {"log2"s, TT::LOG2}, {"log10"s, TT::LOG10}, {"log"s, TT::LOG},

        {"round"s, TT::ROUND}, {"ceil"s, TT::CEIL}, {"floor"s, TT::FLOOR}, {"trunc"s, TT::TRUNC},

        {"sin"s, TT::SIN}, {"cos"s, TT::COS}, {"tan"s, TT::TAN}, {"cot"s, TT::COT},
        {"asin"s, TT::ARCSIN}, {"acos"s, TT::ARCCOS}, {"atan"s, TT::ARCTAN}, {"acot"s, TT::ARCCOT},
        {"arcsin"s, TT::ARCSIN}, {"arccos"s, TT::ARCCOS}, {"arctan"s, TT::ARCTAN}, {"arccot"s, TT::ARCCOT},

        {"sum"s, TT::SUM}, {"max"s, TT::MAX}, {"min"s, TT::MIN}, {"avg"s, TT::AVG},

        {"concat"s, TT::CONCAT}, {"lower"s, TT::LOWER}, {"upper"s, TT::UPPER},
        //{""s, TT::},
    };
};
} // namespace cz::lastaapps::vimxel:expr

#endif