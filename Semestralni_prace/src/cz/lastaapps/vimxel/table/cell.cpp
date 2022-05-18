#include "cell.hpp"
using namespace std;
namespace cz::lastaapps::vimxel::table {

// --- TextCell ---------------------------------------------------------------
TextCell::TextCell(string content, SSingleTerm term, bool inCycle)
    : mContent(move(content)), mTerm(term), mInCycle(inCycle) {}

const string& TextCell::getContent() const {
	return mContent;
}
string TextCell::getValue() const {
	if (mInCycle) return "CYCLE!";
	return mTerm->toString();
}
SSingleTerm TextCell::getTerm() const {
	if (mInCycle) return EMPTY_TERM;
	return mTerm;
}
bool TextCell::isInCycle() const {
	return mInCycle;
}
Cell* TextCell::clone() const {
	return new TextCell(*this);
}

// --- EmptyCell --------------------------------------------------------------
const string& EmptyCell::getContent() const { return emptyString; }
string EmptyCell::getValue() const { return ""; }
SSingleTerm EmptyCell::getTerm() const {
	return EMPTY_TERM;
}
bool EmptyCell::isInCycle() const { return false; }

Cell* EmptyCell::clone() const {
	return new EmptyCell(*this);
}

}  // namespace cz::lastaapps::vimxel::table