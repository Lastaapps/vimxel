#include "table.hpp"

#include <cmath>

#include "../expr/parser.hpp"
#include "../expr/tokenizer.hpp"
#include "../log.hpp"
#include "cell.hpp"

namespace cz::lastaapps::vimxel::table {

// --- Table ------------------------------------------------------------------
const Cell& Table::getCell(const Coordinates& coord) const {
	const auto iter = mMap.find(coord);
	if (iter == mMap.end())
		return emptyCell;
	return *(iter->second);
}
void Table::deleteCell(const Coordinates& coord) {
	mMap.erase(coord);
}
void Table::deleteAll() {
	vector<Coordinates> coords;
	for (const auto& item : mMap)
		coords.emplace_back(item.first);

	mChanged = false;
	mMap.clear();
	mDependencies.clear();
	mDependenciesInversed.clear();

	for (const auto& item : coords)
		updateContracts(item);
}

shared_ptr<CellContract> Table::createCellContract() {
	class TableCellContract final : public CellContract {
		const Table& mT;

	   public:
		TableCellContract(const Table& t) : mT(t) {}
		string getDataAt(const Coordinates& coord) const override {
			return mT.getCell(coord).getValue();
		}
	};
	auto ptr = shared_ptr<CellContract>(dynamic_cast<CellContract*>(new TableCellContract(*this)));
	mContracts.push_back(ptr);
	return ptr;
}
void Table::updateContracts(const Coordinates& coord) {
	mlog << "Updating data at " << coord << endl;
	for (size_t i = 0; i < mContracts.size(); i++) {
		auto ptr = mContracts[i];
		if (ptr.use_count() <= 1) {
			mContracts.erase(mContracts.begin() + i);
			i--;
		} else {
			ptr->dataUpdatedAt(coord);
		}
	}
}
Coordinates Table::tableSize() const {
	size_t maxX = 0, maxY = 0;
	for (const auto& [key, value] : mMap) {
		if (key.x() > maxX) maxX = key.x();
		if (key.y() > maxY) maxY = key.y();
	}
	return Coordinates(maxX + 1, maxY + 1);  // to convert coordinates to size
}
bool Table::isEmpty() const {
	return mMap.empty();
}
bool Table::changed() const {
	return mChanged;
}
void Table::clearChanged() {
	mChanged = false;
}

// --- Cycles and expressions handling -------------------------------------
void Table::updateCellAll(const Coordinates& coord, const string& content, SSingleTerm term) {
	mMap.insert_or_assign(coord, make_unique<TextCell>(content, term, false));
}
void Table::updateCellInCycle(const Coordinates& coord, bool inCycle) {
	const Cell& current = getCell(coord);
	if (dynamic_cast<const EmptyCell*>(&current) != nullptr) return;

	mMap.insert_or_assign(coord, make_unique<TextCell>(current.getContent(), current.getTerm(), inCycle));
}
bool Table::isCellInCycle(const Coordinates& coord) const {
	return getCell(coord).isInCycle();
}
void Table::updateCellWithResult(const Coordinates& coord, SSingleTerm term) {
	const Cell& current = getCell(coord);
	if (dynamic_cast<const EmptyCell*>(&current) != nullptr) return;

	mMap.insert_or_assign(coord, make_unique<TextCell>(current.getContent(), term, false));
}

Table::TableUpdateResult Table::updateCell(const Coordinates& coord, const string& content) {
	const string oldContent = getCell(coord).getContent();
	destroyOldCell(coord);

	try {
		switch (isExpression(content)) {
		case CT::EMPTY: {
			deleteCell(coord);
			onTextCellUpdated(coord, content);
			break;
		}
		case CT::TEXT: {
			long double numberValue;
			if (tryParseNumber(content, numberValue))
				updateCellAll(coord, content, make_shared<expr::DoubleTerm>(numberValue));
			else
				updateCellAll(coord, content, make_shared<expr::TextTerm>(content));
			onTextCellUpdated(coord, content);
			break;
		}
		case CT::ESCAPED: {
			const string dropFirst = string(content.begin() + 1, content.end());
			long double numberValue;
			if (tryParseNumber(dropFirst, numberValue))
				updateCellAll(coord, content, make_shared<expr::DoubleTerm>(numberValue));
			else
				updateCellAll(coord, content, make_shared<expr::TextTerm>(dropFirst));
			onTextCellUpdated(coord, content);
			break;
		}
		case CT::EXPRESSION: {
			updateCellAll(coord, content, make_shared<expr::DoubleTerm>(0.0L));
			onExpressionCellUpdated(coord, content);
			break;
		}
		default:
			throw runtime_error("Unknown content type");
		}
		mChanged = true;
		return TableUpdateResult{true, ""};
	} catch (exception& e) {
		updateCell(coord, oldContent);
		return TableUpdateResult{false, e.what()};
	}
}
bool Table::tryParseNumber(const string& content, long double& out) {
	string noSpaces;
	for (const char c : content) {
		if (!isspace(c)) noSpaces += tolower(c);
	}
	if (noSpaces.empty()) return false;

	if (noSpaces == "inf") {
		out = INFINITY;
		return true;
	}
	if (noSpaces == "-inf") {
		out = -1 * INFINITY;
		return true;
	}
	if (noSpaces == "nan" || noSpaces == "-nan") {
		out = NAN;
		return true;
	}

	char c;
	auto mPos = noSpaces.begin();
	long double num = 0;
	bool isMinus = false;
	if (*mPos == '-') {
		isMinus = true;
		++mPos;
	}
	while (true) {
		if (mPos == noSpaces.end()) break;
		if (!isdigit(c = *mPos++)) {
			mPos--;
			break;
		}
		num *= 10;
		num += c - '0';
	}
	if (mPos != noSpaces.end()) {
		if (*mPos++ == '.') {
			long double pow = 1;
			while (true) {
				if (mPos == noSpaces.end())
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
	if (mPos != noSpaces.end())
		return false;
	out = isMinus ? -1 * num : num;
	return true;
}
void Table::destroyOldCell(const Coordinates& coord) {
	removeDependencies(coord);
}

void Table::onTextCellUpdated(const Coordinates& coord, const string&) {
	auto range = mDependencies.equal_range(coord);
	for (auto itr = range.first; itr != range.second; ++itr) {
		const Coordinates& dep = itr->second;
		recalculate(dep);
	}
	updateContracts(coord);
}
void Table::onExpressionCellUpdated(const Coordinates& coord, const string& content) {
	const string dropFirst = string(content.begin() + 1, content.end());
	expr::Tokenizer tokenizer(dropFirst);
	tokenizer.skipAll();
	addDependencies(coord, tokenizer.getDependent());
	recalculate(coord);
}
void Table::recalculate(const Coordinates& coord) {
	clearDependent(coord);
	ExecutionPlan plan;
	CycleRootsSet roots;
	createExecutionPlan(coord, plan, roots);
	evaluate(plan, roots);
}

void Table::createExecutionPlan(const Coordinates& coord, ExecutionPlan& plan, CycleRootsSet& cycleRoots) const {
	ExecutionArgs args;
	createExecutionPlanRecursive(coord, args, 1);
	for (const auto& pair : args.order)
		plan.push(ExecutionItem{pair.second, pair.first});
	cycleRoots = args.cycleRoots;
}
void Table::createExecutionPlanRecursive(const Coordinates& coord, ExecutionArgs& args, size_t depth) const {
	bool hasBeenVisited = args.visited.find(coord) != args.visited.end();
	if (hasBeenVisited) {
		args.cycleRoots.insert(coord);
		throw invalid_argument("Cycle found, invalid argument");
		return;
	}
	args.visited.insert(coord);

	auto order = args.order.find(coord);
	if (order == args.order.end() || order->second < depth)
		args.order[coord] = depth;

	++depth;
	auto range = mDependencies.equal_range(coord);
	for (auto itr = range.first; itr != range.second; ++itr) {
		const Coordinates& dest = itr->second;
		createExecutionPlanRecursive(dest, args, depth);
	}
	args.visited.erase(coord);
}
bool Table::ExecutionItem::operator<(const ExecutionItem& other) const {
	if (index > other.index) return true;
	if (index < other.index) return false;
	return coord < other.coord;
}

// evaluation
void Table::evaluate(ExecutionPlan& plan, const CycleRootsSet& cycleRoots) {
	while (!plan.empty()) {
		const Coordinates coord = plan.top().coord;
		plan.pop();
		evaluateCell(coord, cycleRoots);
		updateContracts(coord);
	}
}
void Table::evaluateCell(const Coordinates& coord, const CycleRootsSet& cycleRoots) {
	// are you cycle root
	if (cycleRoots.find(coord) != cycleRoots.end()) {
		updateCellInCycle(coord, true);
		return;
	}
	// evaluate expression
	const string& expression = getCell(coord).getContent();
	auto tokenizer = make_shared<expr::Tokenizer>(string(expression.begin() + 1, expression.end()));

	auto termProvieder = [&](const Coordinates& coord) {
		return getCell(coord).getTerm();
	};
	expr::Parser p(tokenizer, termProvieder);
	auto term = p.evaulate();
	auto singleTerm = dynamic_pointer_cast<expr::SingleTerm>(term);
	if (singleTerm == nullptr)
		throw invalid_argument("Area reference cannot be saved in a cell");
	auto depend = tokenizer->getDependent();

	// do you depend on a cycle or an error
	bool dependOnCycleOrError = checkDependOnCycle(coord, depend);
	if (dependOnCycleOrError) {
		updateCellInCycle(coord, true);
		return;
	}

	// update data in database
	updateCellWithResult(coord, singleTerm);
}

bool Table::checkDependOnCycle(const Coordinates&, const set<Coordinates>& depend) const {
	for (const auto& dep : depend) {
		const Cell& cell = getCell(dep);
		if (cell.isInCycle()) return true;
	}
	return false;
}

void Table::clearDependent(const Coordinates& coord) {
	unordered_set<Coordinates> handled;
	queue<Coordinates> toResolve;
	toResolve.push(coord);
	while (!toResolve.empty()) {
		const Coordinates c = toResolve.front();
		toResolve.pop();
		const auto range = mDependencies.equal_range(c);
		for (auto itr = range.first; itr != range.second; ++itr) {
			const Coordinates& toClear = itr->second;
			auto inSet = handled.find(toClear);
			if (inSet == handled.end()) {
				handled.insert(toClear);
				toResolve.push(toClear);
			}
		}
	}
	for (const auto& toClear : handled)
		updateCellInCycle(toClear, false);
}

void Table::addDependencies(const Coordinates& coord, const set<Coordinates>& depend) {
	for (const auto& dep : depend) {
		mDependencies.emplace(dep, coord);
		mDependenciesInversed.emplace(coord, dep);
	}
}
void Table::removeDependencies(const Coordinates& coord) {
	auto range = mDependenciesInversed.equal_range(coord);
	for (auto itr = range.first; itr != range.second; ++itr) {
		auto secRange = mDependencies.equal_range(itr->second);
		for (auto secItr = secRange.first; secItr != secRange.second;) {
			auto oldItr = secItr;
			secItr++;
			if (oldItr->second == coord)
				mDependencies.erase(oldItr);
		}
	}
	mDependenciesInversed.erase(coord);
}
Table::CellContentType Table::isExpression(const string& text) const {
	using CT = CellContentType;
	if (text.empty()) return CT::EMPTY;
	if (text[0] != '=') return CT::TEXT;
	if (text.size() >= 2 && text[1] == '=') return CT::ESCAPED;
	return CT::EXPRESSION;
}

}  // namespace cz::lastaapps::vimxel::table