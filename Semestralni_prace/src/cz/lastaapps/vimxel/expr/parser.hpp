#ifndef H_PARSER
#define H_PARSER
#include <functional>
#include <memory>

#include "tokenizer.hpp"
#include "../table/coordinate.hpp"

#include "nodes/agregateFunNodes.hpp"
#include "nodes/constantNodes.hpp"
#include "nodes/goniometryNodes.hpp"
#include "nodes/mathFunNodes.hpp"
#include "nodes/mathOperatorNodes.hpp"
#include "nodes/mathProcessNodes.hpp"
#include "nodes/node.hpp"
#include "nodes/termNode.hpp"
#include "nodes/terms.hpp"
#include "nodes/textManipNodes.hpp"

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

	STokenzizer mTokenizer;
	function<SSingleTerm(const table::Coordinates&)> mProvider;
    SToken mToken;

   public:
    Parser(STokenzizer tokenizer, function<SSingleTerm(const table::Coordinates&)> dataProvider);
    STerm evaulate();
    private:
    void nextToken();
    SNode evE();
    SNode evT();
    SNode evF();
    bool evFTerms(SNode&);
    bool evFConstants(SNode&);
    bool evFOperators(SNode&);
    bool evFBrackets(SNode&);
    bool evFFunctions(SNode&);
    template<TT type, size_t size, typename Name>
    bool evFFunctionsCheck(SNode&);
    pair<bool, vector<SNode>> evFFunctionsOperands(const TT type);
};
} // namespace cz::lastaapps::vimxel::exptr



#endif