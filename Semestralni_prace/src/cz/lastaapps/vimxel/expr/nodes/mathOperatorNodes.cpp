#include "mathOperatorNodes.hpp"

#include <stdexcept>

using namespace std;
namespace cz::lastaapps::vimxel::expr {

// plus
string BinPlusNode::getName() const { return "plus"; }
STerm BinPlusNode::getValue() const {
	return make_shared<DoubleTerm>(
	    castedLeft()->getValue() + castedRight()->getValue());
}

// minus
string BinMinusNode::getName() const { return "minus"; }
STerm BinMinusNode::getValue() const {
	return make_shared<DoubleTerm>(
	    castedLeft()->getValue() - castedRight()->getValue());
}

// times
string TimesNode::getName() const { return "times"; }
STerm TimesNode::getValue() const {
	return make_shared<DoubleTerm>(
	    castedLeft()->getValue() * castedRight()->getValue());
}

// divide
string DivideNode::getName() const { return "divide"; }
STerm DivideNode::getValue() const {
	return make_shared<DoubleTerm>(
	    castedLeft()->getValue() / castedRight()->getValue());
}

// plus unary
string UnPlusNode::getName() const { return "unary plus"; }
STerm UnPlusNode::getValue() const {
	return casted();
}

// minus unary
string UnMinusNode::getName() const { return "unary minus"; }
STerm UnMinusNode::getValue() const {
	return make_shared<DoubleTerm>(-1 * casted()->getValue());
}

}  // namespace cz::lastaapps::vimxel::expr