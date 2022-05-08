#include "parser.hpp"

using namespace std;
using namespace cz::lastaapps::vimxel::table;
namespace cz::lastaapps::vimxel::expr {

Parser::Parser(STokenzizer tokenizer, function<SSingleTerm(const table::Coordinates&)> dataProvider)
    : mTokenizer(tokenizer), mProvider(dataProvider) {}

STerm Parser::evaulate() {
	nextToken();
	if (mToken->type == TT::NONE)
		throw invalid_argument("Empty exression");
	return evE()->getValue();
}

void Parser::nextToken() {
	mToken = mTokenizer->nextToken();
}
#define mcase(A, B) \
	case (A): {     \
		B           \
	} break;
SNode Parser::evE() {
	SNode node = evT();
	while (true) {
		switch (mToken->type) {
			mcase(TT::PLUS, {
				nextToken();
				node = make_shared<BinPlusNode>(node, evT());
			}) mcase(TT::MINUS, {
				nextToken();
				node = make_shared<BinMinusNode>(node, evT());
			}) default : return node;
		}
	}
}
SNode Parser::evT() {
	SNode node = evF();
	while (true) {
		switch (mToken->type) {
			mcase(TT::TIMES, {
				nextToken();
				node = make_shared<BinTimesNode>(node, evF());
			}) mcase(TT::DIVIDE, {
				nextToken();
				node = make_shared<BinDivideNode>(node, evF());
			}) mcase(TT::MODULO, {
				nextToken();
				node = make_shared<ModuloNode>(node, evF());
			}) default : return node;
		}
	}
}
SNode Parser::evF() {
	SNode out;
	if (evFTerms(out)) return out;
	if (evFConstants(out)) return out;
	if (evFOperators(out)) return out;
	throw invalid_argument("Expected number or nested expression");
}

bool Parser::evFTerms(SNode& out) {
	switch (mToken->type) {
		mcase(TT::DOUBLE, {
			const auto casted = static_pointer_cast<DoubleToken>(mToken);
			nextToken();
			out = make_shared<TermNode>(make_shared<DoubleTerm>(casted->payload));
		}) mcase(TT::TEXT, {
			const auto casted = static_pointer_cast<TextToken>(mToken);
			nextToken();
			out = make_shared<TermNode>(make_shared<TextTerm>(casted->payload));
		}) mcase(TT::CELL, {
			const auto casted = static_pointer_cast<CellToken>(mToken);
			const auto term = mProvider(casted->payload);
			nextToken();
			out = make_shared<TermNode>(term);
		}) mcase(TT::SELECTION, {
			const auto casted = static_pointer_cast<SelectionToken>(mToken);
			const table::Selection selection = casted->payload;
			vector<SSingleTerm> terms;
			selection.iterateOver([&](const Coordinates& coord) {
				terms.push_back(mProvider(coord));
			});
			nextToken();
			out = make_shared<TermNode>(make_shared<AreaTerm>(terms));
		}) default : return false;
	}
	return true;
}

bool Parser::evFConstants(SNode& out) {
	switch (mToken->type) {
		mcase(TT::PI, {
			nextToken();
			out = make_shared<PiNode>();
		})
		mcase(TT::E, {
			nextToken();
			out = make_shared<EulersNumberNode>();
		})
		mcase(TT::LIGHT_SPEED, {
			nextToken();
			out = make_shared<LightSpeedNode>();
		})
		mcase(TT::GOLDEN_RATION, {
			nextToken();
			out = make_shared<GoldenRationNode>();
		})
		default : return false;
	}
	return true;
}

bool Parser::evFOperators(SNode& out) {
	switch (mToken->type) {
		mcase(TT::PLUS, {
			nextToken();
			out = make_shared<UnPlusNode>(evF());
		}) mcase(TT::MINUS, {
			nextToken();
			out = make_shared<UnMinusNode>(evF());
		}) default : return false;
	}
	return true;
}

#undef mcase
}  // namespace cz::lastaapps::vimxel::expr