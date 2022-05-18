#include "parserTester.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {

void ParserTester::operator()() {
	cout << "Testing parser" << endl;
	testExprs();
}

#define p(s)                                        \
	{                                               \
		auto tokenizer = make_shared<Tokenizer>(s); \
		Parser(tokenizer, provider).evaluate();     \
	}

void ParserTester::testExprs() {
	p("1");
	p("+ 1");
	p("1 + 1");
	p("1 + (1 * 2)");
	p("max(1, (1 * 2), 69)");
	p("concat(1, (1 * 2), 69, 'm')");

	shouldThrow(p(""));
	shouldThrow(p("1 + 1 +"));
	shouldThrow(p("1 + ( 2 * 4"));
	shouldThrow(p("pow(0)"));
	shouldThrow(p("pow(0, 0, 0)"));
	shouldThrow(p("pow(0, 0,)"));
	shouldThrow(p("pow(' ', ' ')"));
	shouldThrow(p("A1:A2:A2"));
	shouldThrow(p("concat(A1:A2)"));
	shouldThrow(p("max()"));
	shouldThrow(p("sin(1"));
	shouldThrow(p("sin(1,"));
	shouldThrow(p("hello(1)"));
	shouldThrow(p("upper(1)"));
	shouldThrow(p("1 + (2 * 3}"));
	shouldThrow(p("1 + 1 }"));
}

};  // namespace cz::lastaapps::vimxel::expr