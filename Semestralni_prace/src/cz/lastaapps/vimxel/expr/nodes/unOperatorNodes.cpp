#include "unOperatorNodes.hpp"
#include <stdexcept>


using namespace std;
namespace cz::lastaapps::vimxel::expr {

// unary general
UnOpNode::UnOpNode(SNode child)
: mChild(child ) {}

// unary number operator
shared_ptr<DoubleTerm> UnOpNumNode::casted() const {
	auto casted = dynamic_pointer_cast<DoubleTerm>(mChild->getValue());
	if (casted == nullptr)
		throw invalid_argument(getName() + ": operant in not a number");
	return casted;
}

// unary text operator
shared_ptr<TextTerm> UnOpTextNode::casted() const {
	auto casted = dynamic_pointer_cast<TextTerm>(mChild->getValue());
	if (casted == nullptr)
		throw invalid_argument(getName() + ": operant in not a text");
	return casted;
}

}  