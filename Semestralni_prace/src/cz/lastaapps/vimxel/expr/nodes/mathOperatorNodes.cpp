#include "mathOperatorNodes.hpp"
#include <stdexcept>

using namespace std;
namespace cz::lastaapps::vimxel::expr {

// plus
string BinPlusNode::getName() const { return "plus"; }
ST BinPlusNode::getValue() const {
	return make_shared<DoubleTerm>(
	    castedLeft()->getValue() + castedRight()->getValue());
}

// minus
string BinMinusNode::getName() const { return "minus"; }
ST BinMinusNode::getValue() const {
	return make_shared<DoubleTerm>(
	    castedLeft()->getValue() - castedRight()->getValue());
}

// times
string BinTimesNode::getName() const { return "times"; }
ST BinTimesNode::getValue() const {
	return make_shared<DoubleTerm>(
	    castedLeft()->getValue() * castedRight()->getValue());
}

// divide
string BinDivideNode::getName() const { return "divide"; }
ST BinDivideNode::getValue() const {
	return make_shared<DoubleTerm>(
	    castedLeft()->getValue() / castedRight()->getValue());
}

// plus unary
string UnPlusNode::getName() const { return "unary plus"; }
ST UnPlusNode::getValue() const {
	return casted();
}

// minus unary
string UnMinusNode::getName() const { return "unary minus"; }
ST UnMinusNode::getValue() const {
	return make_shared<DoubleTerm>(-1 * casted() -> getValue());
}

}