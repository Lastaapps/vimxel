#include "multiOperatorNodes.hpp"

#include <stdexcept>
#include <algorithm>

using namespace std;
namespace cz::lastaapps::vimxel::expr {

// general n-ary operator
MultiOpNode::MultiOpNode(const vector<SN>& children)
    : mChildren(map(children)) {}

vector<ST> MultiOpNode::map(const vector<SN>& src) {
	vector<ST> result;
	auto mapper = [](const SN& st) { return st->getValue(); };
	transform(src.begin(), src.end(), back_inserter(result), mapper);
    return result;
}

// just numbers
MultiOpNumNode::MultiOpNumNode(const vector<SN>& children)
:MultiOpNode(children) {
    for (const auto& term : mChildren) {
        auto castedDouble = dynamic_pointer_cast<DoubleTerm>(term);
        if (castedDouble != nullptr) continue;
		throw invalid_argument(getName() + ": at least one arg in not a number");
	}
}

// numbers or area
MultiOpNumOrAreaNode::MultiOpNumOrAreaNode(const vector<SN>& children)
:MultiOpNode(children) {
    for (const auto& term : mChildren) {
        auto castedDouble = dynamic_pointer_cast<DoubleTerm>(term);
        if (castedDouble != nullptr) continue;
        auto castedArea = dynamic_pointer_cast<AreaTerm>(term);
        if (castedArea != nullptr) continue;
		throw invalid_argument(getName() + ": at least one arg in not a number or an area");
	}
}

// number or text
MultiOpNumOrTextNode::MultiOpNumOrTextNode(const vector<SN>& children)
:MultiOpNode(children) {
    for (const auto& term : mChildren) {
        auto castedDouble = dynamic_pointer_cast<DoubleTerm>(term);
        if (castedDouble != nullptr) continue;
        auto castedText = dynamic_pointer_cast<TextTerm>(term);
        if (castedText != nullptr) continue;
		throw invalid_argument(getName() + ": at least one arg in not a number or a text");
	}
}

// just text
MultiOpTextNode::MultiOpTextNode(const vector<SN>& children)
:MultiOpNode(children) {
    for (const auto& term : mChildren) {
        auto castedText = dynamic_pointer_cast<TextTerm>(term);
        if (castedText != nullptr) continue;
		throw invalid_argument(getName() + ": at least one arg in not a text");
	}
}

}  // namespace cz::lastaapps::vimxel::expr