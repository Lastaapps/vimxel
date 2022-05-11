#include "aggregateFunNodes.hpp"

#include <stdexcept>

using namespace std;
namespace cz::lastaapps::vimxel::expr {

// sum
string SumNode::getName() const { return "sum"; }
STerm SumNode::getValue() const {
	long double sum = 0;
	for (const auto& term : checked())
		addTerm(term, sum);
	return make_shared<DoubleTerm>(sum);
}
void SumNode::addTerm(STerm term, long double& sum) const {
	auto castedDouble = dynamic_pointer_cast<DoubleTerm>(term);
	if (castedDouble != nullptr) {
		sum += castedDouble->getValue();
		return;
	}

	auto castedArea = dynamic_pointer_cast<AreaTerm>(term);
	if (castedArea != nullptr) {
		for (const auto& child : castedArea->getValue())
			addTerm(child, sum);
		return;
	}
	throw invalid_argument(getName() + ": summing of nonnumber term");
}

// max
string MaxNode::getName() const { return "max"; }
STerm MaxNode::getValue() const {
	if (mChildren.empty())
		throw invalid_argument("Max of no elements is undefined");

	const auto children = checked();
	long double max = getFirst(children[0]);
	for (const auto& term : children)
		checkTerm(term, max);
	return make_shared<DoubleTerm>(max);
}
long double MaxNode::getFirst(STerm term) const {
	auto castedDouble = dynamic_pointer_cast<DoubleTerm>(term);
	if (castedDouble != nullptr)
		return castedDouble->getValue();

	auto castedArea = dynamic_pointer_cast<AreaTerm>(term);
	if (castedArea != nullptr)
		return getFirst(castedArea->getValue()[0]);

	throw(getName() + ": max of nonnumber term");
}
void MaxNode::checkTerm(STerm term, long double& max) const {
	auto castedDouble = dynamic_pointer_cast<DoubleTerm>(term);
	if (castedDouble != nullptr) {
		if (castedDouble->getValue() > max)
			max = castedDouble->getValue();
		return;
	}

	auto castedArea = dynamic_pointer_cast<AreaTerm>(term);
	if (castedArea != nullptr) {
		for (const auto& child : castedArea->getValue())
			checkTerm(child, max);
		return;
	}
	throw(getName() + ": max of nonnumber term");
}

// min
string MinNode::getName() const { return "min"; }
STerm MinNode::getValue() const {
	if (mChildren.empty())
		throw invalid_argument("Min of no elements is undefined");

	const auto children = checked();
	long double min = getFirst(children[0]);
	for (const auto& term : children)
		checkTerm(term, min);
	return make_shared<DoubleTerm>(min);
}
long double MinNode::getFirst(STerm term) const {
	auto castedDouble = dynamic_pointer_cast<DoubleTerm>(term);
	if (castedDouble != nullptr)
		return castedDouble->getValue();

	auto castedArea = dynamic_pointer_cast<AreaTerm>(term);
	if (castedArea != nullptr)
		return getFirst(castedArea->getValue()[0]);

	throw(getName() + ": max of nonnumber term");
}
void MinNode::checkTerm(STerm term, long double& min) const {
	auto castedDouble = dynamic_pointer_cast<DoubleTerm>(term);
	if (castedDouble != nullptr) {
		if (castedDouble->getValue() < min)
			min = castedDouble->getValue();
		return;
	}

	auto castedArea = dynamic_pointer_cast<AreaTerm>(term);
	if (castedArea != nullptr) {
		for (const auto& child : castedArea->getValue())
			checkTerm(child, min);
		return;
	}
	throw(getName() + ": min of nonnumber term");
}

// avg
string AvgNode::getName() const { return "avg"; }
STerm AvgNode::getValue() const {
	long double sum = 0;
	size_t total = 0;
	for (const auto& term : checked())
		addTerm(term, sum, total);

	if (total == 0)
		throw invalid_argument(getName() + ": of no elements is not defined");

	return make_shared<DoubleTerm>(sum / total);
}
void AvgNode::addTerm(STerm term, long double& sum, size_t& total) const {
	auto castedDouble = dynamic_pointer_cast<DoubleTerm>(term);
	if (castedDouble != nullptr) {
		sum += castedDouble->getValue();
		total++;
		return;
	}

	auto castedArea = dynamic_pointer_cast<AreaTerm>(term);
	if (castedArea != nullptr) {
		for (const auto& child : castedArea->getValue())
			addTerm(child, sum, total);
		return;
	}
	throw invalid_argument(getName() + ": summing of nonnumber term");
}
}  // namespace cz::lastaapps::vimxel::expr