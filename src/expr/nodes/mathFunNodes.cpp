#include "mathFunNodes.hpp"

#include <cmath>

using namespace std;
namespace cz::lastaapps::vimxel::expr {

// pow
string PowNode::getName() const { return "pow"; }
STerm PowNode::getValue() const {
	return make_shared<DoubleTerm>(
	    powl(castedLeft()->getValue(), castedRight()->getValue()));
}

// sqrt
string SqrtNode::getName() const { return "sqrt"; }
STerm SqrtNode::getValue() const {
	return make_shared<DoubleTerm>(
	    sqrtl(casted()->getValue()));
}

// abs
string AbsNode::getName() const { return "abs"; }
STerm AbsNode::getValue() const {
	return make_shared<DoubleTerm>(
	    fabsl(casted()->getValue()));
}

// modulo
string ModuloNode::getName() const { return "modulo"; }
STerm ModuloNode::getValue() const {
	return make_shared<DoubleTerm>(
	    fmodl(castedLeft()->getValue(), castedRight()->getValue()));
}

// e
string ExponentialNode::getName() const { return "e"; }
STerm ExponentialNode::getValue() const {
	return make_shared<DoubleTerm>(
	    expl(casted()->getValue()));
}

// ln
string LnNode::getName() const { return "ln"; }
STerm LnNode::getValue() const {
	return make_shared<DoubleTerm>(
	    logl(casted()->getValue()));
}

// log2
string Log2Node::getName() const { return "log2"; }
STerm Log2Node::getValue() const {
	return make_shared<DoubleTerm>(
	    log2l(casted()->getValue()));
}

// log10
string Log10Node::getName() const { return "log10"; }
STerm Log10Node::getValue() const {
	return make_shared<DoubleTerm>(
	    log10l(casted()->getValue()));
}

// log
string LogNode::getName() const { return "log"; }
STerm LogNode::getValue() const {
	return make_shared<DoubleTerm>(
	    logl(castedLeft()->getValue()) / logl(castedRight()->getValue()));
}

}  // namespace cz::lastaapps::vimxel::expr