#include "tokenizer.hpp"

#include <stdexcept>

#include "../log.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
Tokenizer::Tokenizer(const string& string)
    : mString(string), mPos(mString.begin()) {}

shared_ptr<Token> Tokenizer::nextToken() {
	if (mPos == mString.end())
		return make_shared<Token>(TT::NONE);

	skipSpaces();
	log("Tokenizing '"s + *mPos + "' at index: " + to_string(distance(mString.begin(), mPos)));

	SToken token;
	if (parseOperators(token)) {
		log("Tokenized as operator");
		return token;
	}
	if (parseNumber(token)) {
		log("Tokenized as number");
		return token;
	}
	if (parseText(token)) {
		log("Tokenized as text");
		return token;
	}
	if (parseCell(token)) {
		log("Tokenized as cell");
		return token;
	}
	if (parseFun(token)) {
		log("Tokenized as fun");
		return token;
	}
	throw invalid_argument("Unexpected character at position: "s + to_string(mPos - mString.begin()));
}

void Tokenizer::skipAll() {
	while (nextToken()->type != TT::NONE)
		;
}

bool Tokenizer::parseOperators(SToken& out) {
	char c = *mPos++;
	switch (c) {
	case ',':
	case ';':
		out = make_shared<Token>(TT::COMMA);
		return true;
	case '+':
		out = make_shared<Token>(TT::PLUS);
		return true;
	case '-':
		out = make_shared<Token>(TT::MINUS);
		return true;
	case '*':
		out = make_shared<Token>(TT::TIMES);
		return true;
	case '/':
		out = make_shared<Token>(TT::DIVIDE);
		return true;
	case '%':
		out = make_shared<Token>(TT::MODULO);
		return true;
	case '(':
		out = make_shared<Token>(TT::BRACKET_LS);
		return true;
	case ')':
		out = make_shared<Token>(TT::BRACKET_RS);
		return true;
	case '[':
		out = make_shared<Token>(TT::BRACKET_LM);
		return true;
	case ']':
		out = make_shared<Token>(TT::BRACKET_RM);
		return true;
	case '{':
		out = make_shared<Token>(TT::BRACKET_LL);
		return true;
	case '}':
		out = make_shared<Token>(TT::BRACKET_RL);
		return true;
	}
	mPos--;
	return false;
}

bool Tokenizer::parseNumber(SToken& out) {
	char c;
	const SItr start = mPos;
	long double num = 0;
	while (true) {
		if (mPos == mString.end()) break;
		if (!isdigit(c = *mPos++)) {
			mPos--;
			break;
		}
		num *= 10;
		num += c - '0';
	}
	if (mPos != mString.end()) {
		if (*mPos++ == '.') {
			long double pow = 1;
			while (true) {
				if (mPos == mString.end())
					break;
				if (!isdigit(c = *mPos++)) {
					--mPos;
					break;
				}
				pow *= 10;
				num += (c - '0') / pow;
			}
		} else
			mPos--;
	}
	if (start != mPos) {
		out = make_shared<DoubleToken>(num);
		return true;
	}
	return false;
}

bool Tokenizer::parseText(SToken& out) {
	char c = *mPos++;
	if (c != '"' && c != '\'') {
		mPos--;
		return false;
	}
	if (mPos == mString.end())
		throw invalid_argument("Empty and unended text literal");

	char start = c;
	string content;
	while (mPos != mString.end() && (c = *mPos++, c != start)) {
		content += c;
	}
	if (c != start)
		throw invalid_argument("Unended text literal");
	out = make_shared<TextToken>(content);
	return true;
}

bool Tokenizer::parseCell(SToken& out) {
	char c = *mPos;
	if ('A' > c || c > 'Z')
		return false;

	string cellName = "";
	size_t cellIndex = 0;
	while (true) {
		if (mPos == mString.end()) break;
		if (!(c = *mPos++, 'A' <= c && c <= 'Z')) {
			mPos--;
			break;
		}
		cellName += c;
	}
	while (true) {
		if (mPos == mString.end()) break;
		if (!(c = *mPos++, '0' <= c && c <= '9')) {
			mPos--;
			break;
		}
		cellIndex *= 10;
		cellIndex += c - '0';
	}
	if (cellName.empty() || cellIndex == 0) return false;
	auto local = table::Coordinates(cellName, cellIndex);

	skipSpaces();  // to allow A2 : B3 syntax with spaces
	if (mPos != mString.end()) {
		if (c = *mPos++, c == ':') {
			skipSpaces();
			SToken own;
			if (parseCell(own)) {
				shared_ptr<CellToken> casted;
				if ((casted = dynamic_pointer_cast<CellToken>(own)) == nullptr)
					throw invalid_argument("Selection cannot contain more :");

				table::Coordinates taken = casted->payload;

				auto selection = table::Selection(local, taken);
				updateDepend(selection);
				out = make_shared<SelectionToken>(selection);
				return true;
			} else {
				throw invalid_argument("Incomplete selection");
			}
		} else {
			mPos--;
		}
	}

	updateDepend(local);
	out = make_shared<CellToken>(local);
	return true;
}

bool Tokenizer::parseFun(SToken& out) {
	char c = *mPos++;
	if (c < 'a' || 'z' < c) {
		mPos--;
		return false;
	}
	string funName;
	funName += c;
	while (true) {
		if (mPos == mString.end()) break;
		if (!(c = *mPos++, ('a' <= c && c <= 'z') || ('0' <= c && c <= '9'))) {
			mPos--;
			break;
		}
		funName += c;
	}
	auto item = mFunMapper.find(funName);
	if (item == mFunMapper.end()) throw invalid_argument("Function "s + funName + " not supported");
	out = make_shared<Token>(item->second);
	return true;
}

void Tokenizer::skipSpaces() {
	while (true) {
		if (mPos == mString.end()) break;
		if (!isspace(*mPos++)) {
			mPos--;
			break;
		}
	}
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