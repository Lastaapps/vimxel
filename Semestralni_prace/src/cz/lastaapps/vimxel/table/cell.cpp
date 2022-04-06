#include "cell.hpp"
using namespace std;
namespace cz::lastaapps::vimxel::table {

// --- TextCell ---------------------------------------------------------------
TextCell::TextCell(string content) : mContent(move(content)) {}
const string& TextCell::getContent() const {
	return mContent;
}

// --- EmptyCell --------------------------------------------------------------
const string& EmptyCell::getContent() const { return emptyString; }

}  // namespace cz::lastaapps::vimxel::table