#ifndef H_PARSER
#define H_PARSER
#include <functional>
#include <memory>

#include "tokenizer.hpp"
#include "nodes/terms.hpp"
#include "../table/coordinate.hpp"

using namespace std;
using namespace cz::lastaapps::vimxel::table;
namespace cz::lastaapps::vimxel::expr {

class Parser final {
	using STokenzizer = shared_ptr<Tokenizer>;
	using ST = shared_ptr<Term>;

   public:
    Parser(STokenzizer, function<ST(const table::Coordinates&)>);
    ST evaulate();
};
} // namespace cz::lastaapps::vimxel::exptr



#endif