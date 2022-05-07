#include "textManipNodes.hpp"
#include <sstream>

using namespace std;
namespace cz::lastaapps::vimxel::expr {

string ConcatNode::getName() const { return "concat"; }
ST ConcatNode::getValue() const {
    ostringstream text;
    text.precision(8);
    for (const auto& term : mChildren) {
        auto castedText = dynamic_pointer_cast<TextTerm>(term);
        if (castedText != nullptr) {
			text << castedText -> getValue();
            continue;
        }
        auto castedDouble = dynamic_pointer_cast<DoubleTerm>(term);
        if (castedDouble != nullptr) {
			text<< castedDouble -> getValue();
            continue;
		}
		// else shouldn't happen
	}
    return make_shared<TextTerm>(text.str());
}

// lower
string LowerNode::getName() const { return "lower"; }
ST LowerNode::getValue() const {
    string text = casted() -> getValue();
    for (auto itr = text.begin(); itr != text.end(); ++itr)
        *itr = tolower(*itr);
    return make_shared<TextTerm>(text);
}

// upper
string UpperNode::getName() const { return "upper"; }
ST UpperNode::getValue() const {
    string text = casted() -> getValue();
    for (auto itr = text.begin(); itr != text.end(); ++itr)
        *itr = toupper(*itr);
    return make_shared<TextTerm>(text);
}

}  