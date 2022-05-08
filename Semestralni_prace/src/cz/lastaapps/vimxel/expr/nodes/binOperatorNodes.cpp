#include "binOperatorNodes.hpp"

#include <stdexcept>

using namespace std;
namespace cz::lastaapps::vimxel::expr {

// binary general
BinOpNode::BinOpNode(SNode left, SNode right)
    : mLeft(left), mRight(right) {}

// binary number only
shared_ptr<DoubleTerm> BinOpNumNode::castedLeft() const {
	auto casted = dynamic_pointer_cast<DoubleTerm>(mLeft->getValue());
	if (casted == nullptr)
		throw invalid_argument(getName() + ": left operant in not a number");
	return casted;
}
shared_ptr<DoubleTerm> BinOpNumNode::castedRight() const {
	auto casted = dynamic_pointer_cast<DoubleTerm>(mRight->getValue());
	if (casted == nullptr)
		throw invalid_argument(getName() + ": right operant in not a number");
	return casted;
}

// binary text only
shared_ptr<TextTerm> BinOpTextNode::castedLeft() const {
	auto casted = dynamic_pointer_cast<TextTerm>(mLeft->getValue());
	if (casted == nullptr)
		throw invalid_argument(getName() + ": left operant in not a text");
	return casted;
}
shared_ptr<TextTerm> BinOpTextNode::castedRight() const {
	auto casted = dynamic_pointer_cast<TextTerm>(mRight->getValue());
	if (casted == nullptr)
		throw invalid_argument(getName() + ": right operant in not a text");
	return casted;
}

}  // namespace cz::lastaapps::vimxel::expr