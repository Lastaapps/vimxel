#include "textManipNodes.hpp"

#include <sstream>

using namespace std;
namespace cz::lastaapps::vimxel::expr {

string ConcatNode::getName() const { return "concat"; }
STerm ConcatNode::getValue() const {
	ostringstream text;
	for (const auto& term : checked())
		text << term->toString();

	return make_shared<TextTerm>(text.str());
}

// lower
string LowerNode::getName() const { return "lower"; }
STerm LowerNode::getValue() const {
	string text = casted()->getValue();
	for (auto itr = text.begin(); itr != text.end(); ++itr)
		*itr = tolower(*itr);
	return make_shared<TextTerm>(text);
}

// upper
string UpperNode::getName() const { return "upper"; }
STerm UpperNode::getValue() const {
	string text = casted()->getValue();
	for (auto itr = text.begin(); itr != text.end(); ++itr)
		*itr = toupper(*itr);
	return make_shared<TextTerm>(text);
}

}  // namespace cz::lastaapps::vimxel::expr