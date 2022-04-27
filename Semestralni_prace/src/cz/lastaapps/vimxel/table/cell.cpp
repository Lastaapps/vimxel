#include "cell.hpp"
using namespace std;
namespace cz::lastaapps::vimxel::table {

// --- TextCell ---------------------------------------------------------------
TextCell::TextCell(string content) : mContent(move(content)) {}
const string& TextCell::getContent() const {
	return mContent;
}
Cell* TextCell::clone() const {
	return new TextCell(*this);
}

// --- EmptyCell --------------------------------------------------------------
const string& EmptyCell::getContent() const { return emptyString; }
Cell* EmptyCell::clone() const {
	return new EmptyCell(*this);
}

}  // namespace cz::lastaapps::vimxel::table