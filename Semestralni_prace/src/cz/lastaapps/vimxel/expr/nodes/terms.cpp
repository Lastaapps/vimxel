#include "terms.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {

DoubleTerm::DoubleTerm(long double value)
    : mValue(value) {}
long double DoubleTerm::getValue() const { return mValue; }

TextTerm::TextTerm(const string& value)
    : mValue(value) {}
const string& TextTerm::getValue() const { return mValue; }

AreaTerm::AreaTerm(vector<shared_ptr<SingleTerm>> value)
    : mValue(value) {}
const vector<shared_ptr<SingleTerm>>& AreaTerm::getValue() const {
	return mValue;
}
}  // namespace cz::lastaapps::vimxel::expr