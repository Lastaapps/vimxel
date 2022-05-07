#include "parser.hpp"

using namespace std;
using namespace cz::lastaapps::vimxel::table;
namespace cz::lastaapps::vimxel::expr {

Parser::Parser(STokenzizer, function<ST(const table::Coordinates&)>){}
shared_ptr<Term> Parser::evaulate() {
    return make_shared<TextTerm>("Juhu");
}
} 