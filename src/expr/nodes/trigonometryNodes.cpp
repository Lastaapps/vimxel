#include "trigonometryNodes.hpp"

#include <cmath>

using namespace std;
namespace cz::lastaapps::vimxel::expr {

// sin
string SinNode::getName() const { return "sin"; }
STerm SinNode::getValue() const {
	return make_shared<DoubleTerm>(sinl(casted()->getValue()));
}

// cost
string CosNode::getName() const { return "cos"; }
STerm CosNode::getValue() const {
	return make_shared<DoubleTerm>(cosl(casted()->getValue()));
}

// tan
string TanNode::getName() const { return "tan"; }
STerm TanNode::getValue() const {
	return make_shared<DoubleTerm>(tanl(casted()->getValue()));
}

// cot
string CotNode::getName() const { return "cot"; }
STerm CotNode::getValue() const {
	return make_shared<DoubleTerm>(1 / tanl(casted()->getValue()));
}

// arcsin
string ArcsinNode::getName() const { return "arcsin"; }
STerm ArcsinNode::getValue() const {
	return make_shared<DoubleTerm>(asinl(casted()->getValue()));
}

// arccos
string ArccosNode::getName() const { return "arccos"; }
STerm ArccosNode::getValue() const {
	return make_shared<DoubleTerm>(acosl(casted()->getValue()));
}

// arctan
string ArctanNode::getName() const { return "arctan"; }
STerm ArctanNode::getValue() const {
	return make_shared<DoubleTerm>(atanl(casted()->getValue()));
}

// arccot
string ArccotNode::getName() const { return "arccot"; }
STerm ArccotNode::getValue() const {
	return make_shared<DoubleTerm>(atanl(1 / (casted()->getValue())));
}
}  // namespace cz::lastaapps::vimxel::expr