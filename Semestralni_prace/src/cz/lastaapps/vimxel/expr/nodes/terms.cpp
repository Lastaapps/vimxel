#include "terms.hpp"

#include <sstream>

using namespace std;
namespace cz::lastaapps::vimxel::expr {

DoubleTerm::DoubleTerm(long double value)
    : mValue(value) {}
long double DoubleTerm::getValue() const { return mValue; }
string DoubleTerm::toString() const {
	ostringstream text;
	text.precision(6);
	text << mValue;
	return text.str();
}

TextTerm::TextTerm(const string& value)
    : mValue(value) {}
const string& TextTerm::getValue() const { return mValue; }
string TextTerm::toString() const {
	return mValue;
}

AreaTerm::AreaTerm(const vector<shared_ptr<SingleTerm>>& value)
    : mValue(value) {}
const vector<shared_ptr<SingleTerm>>& AreaTerm::getValue() const {
	return mValue;
}
string AreaTerm::toString() const {
	return "Area of "s + to_string(mValue.size());
}
}  // namespace cz::lastaapps::vimxel::expr