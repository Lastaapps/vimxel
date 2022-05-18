#include "parser.hpp"

using namespace std;
using namespace cz::lastaapps::vimxel::table;
namespace cz::lastaapps::vimxel::expr {

Parser::Parser(STokenzizer tokenizer, function<SSingleTerm(const table::Coordinates&)> dataProvider)
    : mTokenizer(tokenizer), mProvider(dataProvider) {}

STerm Parser::evaluate() {
	nextToken();
	if (mToken->type == TT::NONE)
		throw invalid_argument("Empty exression");
	auto tree = evE();
	if (mToken->type != TT::NONE)
		throw invalid_argument("Wrong ending or not opened bracket");
	return tree->getValue();
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
				node = make_shared<TimesNode>(node, evF());
			}) mcase(TT::DIVIDE, {
				nextToken();
				node = make_shared<DivideNode>(node, evF());
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
	if (evFBrackets(out)) return out;
	if (evFFunctions(out)) return out;
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
		}) mcase(TT::E, {
			nextToken();
			out = make_shared<EulersNumberNode>();
		}) mcase(TT::LIGHT_SPEED, {
			nextToken();
			out = make_shared<LightSpeedNode>();
		}) mcase(TT::GOLDEN_RATION, {
			nextToken();
			out = make_shared<GoldenRationNode>();
		}) default : return false;
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

bool Parser::evFBrackets(SNode& out) {
	auto handleBracket = [&](const TT start, const TT end, const char c1, const char c2) {
		if (mToken->type != start) return false;
		nextToken();
		if (mToken->type == end)
			throw invalid_argument("Empty "s + c1 + c2 + " brackers");
		out = evE();
		if (mToken->type != end)
			throw invalid_argument("Bracket "s + c1 + c2 + " not ended");
		nextToken();
		return true;
	};

	if (handleBracket(TT::BRACKET_LS, TT::BRACKET_RS, '(', ')')) return true;
	if (handleBracket(TT::BRACKET_LM, TT::BRACKET_RM, '[', ']')) return true;
	if (handleBracket(TT::BRACKET_LL, TT::BRACKET_RL, '{', '}')) return true;
	return false;
}

bool Parser::evFFunctions(SNode& out) {
	if (evFFunctionsCheck<TT::POW, 2, PowNode>(out)) return true;
	if (evFFunctionsCheck<TT::SQRT, 1, SqrtNode>(out)) return true;
	if (evFFunctionsCheck<TT::ABS, 1, AbsNode>(out)) return true;
	if (evFFunctionsCheck<TT::EXP, 1, ExponentialNode>(out)) return true;
	if (evFFunctionsCheck<TT::LN, 1, LnNode>(out)) return true;
	if (evFFunctionsCheck<TT::LOG2, 1, Log2Node>(out)) return true;
	if (evFFunctionsCheck<TT::LOG10, 1, Log10Node>(out)) return true;
	if (evFFunctionsCheck<TT::LOG, 2, LogNode>(out)) return true;

	if (evFFunctionsCheck<TT::ROUND, 1, RoundNode>(out)) return true;
	if (evFFunctionsCheck<TT::CEIL, 1, CeilNode>(out)) return true;
	if (evFFunctionsCheck<TT::FLOOR, 1, FloorNode>(out)) return true;
	if (evFFunctionsCheck<TT::TRUNC, 1, TruncNode>(out)) return true;

	if (evFFunctionsCheck<TT::SIN, 1, SinNode>(out)) return true;
	if (evFFunctionsCheck<TT::COS, 1, CosNode>(out)) return true;
	if (evFFunctionsCheck<TT::TAN, 1, TanNode>(out)) return true;
	if (evFFunctionsCheck<TT::COT, 1, CotNode>(out)) return true;
	if (evFFunctionsCheck<TT::ARCSIN, 1, ArcsinNode>(out)) return true;
	if (evFFunctionsCheck<TT::ARCCOS, 1, ArccosNode>(out)) return true;
	if (evFFunctionsCheck<TT::ARCTAN, 1, ArctanNode>(out)) return true;
	if (evFFunctionsCheck<TT::ARCCOT, 1, ArccotNode>(out)) return true;

	if (evFFunctionsCheck<TT::SUM, 0, SumNode>(out)) return true;
	if (evFFunctionsCheck<TT::MAX, 0, MaxNode>(out)) return true;
	if (evFFunctionsCheck<TT::MIN, 0, MinNode>(out)) return true;
	if (evFFunctionsCheck<TT::AVG, 0, AvgNode>(out)) return true;

	if (evFFunctionsCheck<TT::CONCAT, 0, ConcatNode>(out)) return true;
	if (evFFunctionsCheck<TT::LOWER, 1, LowerNode>(out)) return true;
	if (evFFunctionsCheck<TT::UPPER, 1, UpperNode>(out)) return true;

	// if (evFFunctionsCheck<TT::>(out)) return true;
	return false;
}
template <TT type, size_t size, typename Name>
bool Parser::evFFunctionsCheck(SNode& out) {
	const auto pair = evFFunctionsOperands(type);
	if (pair.first == false) return false;
	if (size != 0 && size != pair.second.size())
		throw invalid_argument("Wrong number of arguments");
	out = make_shared<Name>(pair.second);
	return true;
}

pair<bool, vector<SNode>> Parser::evFFunctionsOperands(const TT type) {
	vector<SNode> nodes;
	if (mToken->type != type) {
		return make_pair(false, nodes);
	}
	nextToken();
	if (mToken->type != TT::BRACKET_LS)
		throw invalid_argument("Function without () brackets");
	nextToken();
	if (mToken->type != TT::BRACKET_RS) {
		while (true) {
			nodes.emplace_back(evE());
			if (mToken->type == TT::BRACKET_RS)
				break;
			if (mToken->type == TT::COMMA) {
				nextToken();
			} else {
				throw invalid_argument("Function parameters have to be separated by , or ;");
			}
		}
	}
	nextToken();
	return make_pair(true, nodes);
}

#undef mcase
}  // namespace cz::lastaapps::vimxel::expr