#include "multiOperatorNodes.hpp"

#include <algorithm>
#include <stdexcept>

using namespace std;
namespace cz::lastaapps::vimxel::expr {

// general n-ary operator
MultiOpNode::MultiOpNode(const vector<SNode>& children)
    : mChildren(children) {}

vector<STerm> MultiOpNode::mapped() const {
	vector<STerm> result;
	auto mapper = [](const SNode& st) { return st->getValue(); };
	transform(mChildren.begin(), mChildren.end(), back_inserter(result), mapper);
	return result;
}

// just numbers
vector<shared_ptr<DoubleTerm>> MultiOpNumNode::casted() const {
	const auto items = mapped();
	vector<shared_ptr<DoubleTerm>> out;
	for (const auto& term : items) {
		auto castedDouble = dynamic_pointer_cast<DoubleTerm>(term);
		if (castedDouble != nullptr) {
			out.emplace_back(castedDouble);
			continue;
		}
		throw invalid_argument(getName() + ": at least one arg in not a number");
	}
	return out;
}

// numbers or area
vector<STerm> MultiOpNumOrAreaNode::checked() const {
	const auto items = mapped();
	for (const auto& term : items) {
		auto castedDouble = dynamic_pointer_cast<DoubleTerm>(term);
		if (castedDouble != nullptr) continue;
		auto castedArea = dynamic_pointer_cast<AreaTerm>(term);
		if (castedArea != nullptr) continue;
		throw invalid_argument(getName() + ": at least one arg in not a number or an area");
	}
	return items;
}

// number or text
vector<STerm> MultiOpNumOrTextNode::checked() const {
	const auto items = mapped();
	for (const auto& term : items) {
		auto castedDouble = dynamic_pointer_cast<DoubleTerm>(term);
		if (castedDouble != nullptr) continue;
		auto castedText = dynamic_pointer_cast<TextTerm>(term);
		if (castedText != nullptr) continue;
		throw invalid_argument(getName() + ": at least one arg in not a number or a text");
	}
	return items;
}

// just text
vector<shared_ptr<TextTerm>> MultiOpTextNode::casted() const {
	const auto items = mapped();
	vector<shared_ptr<TextTerm>> out;
	for (const auto& term : items) {
		auto castedText = dynamic_pointer_cast<TextTerm>(term);
		if (castedText != nullptr) {
			out.emplace_back(castedText);
			continue;
		}
		throw invalid_argument(getName() + ": at least one arg in not a number");
	}
	return out;
}

}  // namespace cz::lastaapps::vimxel::expr