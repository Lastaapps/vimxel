#include "tokenizer.hpp"
#include <stdexcept>

using namespace std;
namespace cz::lastaapps::vimxel::expr {
Tokenizer::Tokenizer(const string& string)
    : mString(string), mPos(mString.begin()) {}

shared_ptr<Token> Tokenizer::nextToken() {
	skipSpaces();
	Token* token = nullptr;
	if (mPos == mString.end()) {
		token = new Token(TT::NONE);
		return ST(token);
	}
	if (parseOperators(token)) return ST(token);
	if (parseNumber(token)) return ST(token);
	if (parseText(token)) return ST(token);
	if (parseCell(token)) return ST(token);
	if (parseFun(token)) return ST(token);
	if (parseOperators(token)) return ST(token);
	throw invalid_argument("Unexpected character at position: "s + to_string(mPos - mString.begin()));
}

void Tokenizer::skipAll() {
	while (nextToken() -> type != TT::NONE);
}

bool Tokenizer::parseOperators(Token*& out) {
	char c = *mPos++;
	switch (c) {
	case ',':
	case ';':
		out = new Token(TT::COMMA);
		return true;
	case '+':
		out = new Token(TT::PLUS);
		return true;
	case '-':
		out = new Token(TT::MINUS);
		return true;
	case '*':
		out = new Token(TT::TIMES);
		return true;
	case '/':
		out = new Token(TT::DIVIDE);
		return true;
	case '%':
		out = new Token(TT::MODULO);
		return true;
	case '(':
		out = new Token(TT::BRACKET_LS);
		return true;
	case ')':
		out = new Token(TT::BRACKER_RS);
		return true;
	case '[':
		out = new Token(TT::BRACKET_LM);
		return true;
	case ']':
		out = new Token(TT::BRACKER_RM);
		return true;
	case '{':
		out = new Token(TT::BRACKET_LL);
		return true;
	case '}':
		out = new Token(TT::BRACKER_RL);
		return true;
	}
	mPos--;
	return false;
}

bool Tokenizer::parseNumber(Token*& out) {
	char c;
	SItr start = mPos;
	long double num = 0;
	while (mPos != mString.end() && isdigit(c = *mPos++)) {
		num *= 10;
		num += c - '0';
	}
	if (mPos != mString.end()) mPos--;
	if (mPos != mString.end() && *mPos++ == '.') {
		long double pow = 1;
		while (mPos != mString.end() && isdigit(c = *mPos++)) {
			pow *= 10;
			num += (c - '0') / pow;
		}
	}
	if (mPos != mString.end()) mPos--;
	if (start != mPos) {
		out = new DoubleToken(num);
		return true;
	}
	return false;
}

bool Tokenizer::parseText(Token*& out) {
	char c = *mPos++;
	if (c != '"' && c != '\'') {
		mPos--;
		return false;
	}
	char start = c;
	string content;
	content += c;
	while (mPos != mString.end() && (c = *mPos++, c != start)) {
		content += c;
	}
	if (mPos == mString.end())
		throw invalid_argument("Unended text literal");
	out = new TextToken(content);
	return true;
}

bool Tokenizer::parseCell(Token*& out) {
	char c = *mPos;
	if ('A' > c || c > 'Z')
		return false;

	string cellName;
	size_t cellIndex;
	while (mPos != mString.end() && (c = *mPos++, 'A' <= c && c <= 'Z'))
		cellName += c;
	if (mPos != mString.end()) mPos--;
	while (mPos != mString.end() && (c = *mPos++, '0' <= c && c <= '9')) {
		cellIndex *= 10;
		cellIndex += c - '0';
	}
	if (mPos != mString.end()) mPos--;
	if (cellName.empty() || cellIndex == 0) return false;
	auto local = table::Coordinates(cellName, cellIndex);

	skipSpaces();  // to allow A2 : B3 syntax with spaces
	if (mPos != mString.end() && (c = *mPos++, c == ':')) {
		skipSpaces();
		Token* own;
		if (parseCell(own)) {
			CellToken* casted;
			if ((casted = dynamic_cast<CellToken*>(own)) == nullptr)
				throw invalid_argument("Selection cannot contain more :");

			table::Coordinates taken = casted->payload;
			delete casted;

			auto selection = table::Selection(local, taken);
			updateDepend(selection);
			out = new SelectionToken(selection);
			return true;
		} else
			throw invalid_argument("Incomplete selection");
	} else if (mPos != mString.end())
		mPos--;

	updateDepend(local);
	out = new CellToken(local);
	return true;
}

bool Tokenizer::parseFun(Token*& out) {
	char c = *mPos++;
	if (c < 'a' || 'z' < c) {
		mPos--;
		return false;
	}
	string funName;
	funName += c;
	while (mPos != mString.end() && (c = *mPos++, ('a' <= c && c <= 'z') || ('0' <= c && c <= '9'))) {
		funName += c;
	}
	if (mPos != mString.end()) mPos--;
	auto item = mFunMapper.find(funName);
	if (item == mFunMapper.end()) throw invalid_argument("Function "s + funName + " not supported");
	out = new Token(item->second);
	return false;
}

void Tokenizer::skipSpaces() {
	char c;
	while (mPos != mString.end() && isspace(c = *mPos++))
		;
	if (mPos != mString.end())
		mPos--;
}

const set<table::Coordinates>& Tokenizer::getDependent() const { return mDependent; }
void Tokenizer::updateDepend(const table::Selection& sel) {
	sel.iterateOver([&](const table::Coordinates coord) {
		updateDepend(coord);
	});
}
void Tokenizer::updateDepend(const table::Coordinates& coord) {
	mDependent.insert(coord);
}
}  // namespace cz::lastaapps::vimxel::expr