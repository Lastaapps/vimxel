#ifndef TABLE_H
#define TABLE_H
#include <algorithm>
#include <memory>
#include <map>
#include <unordered_map>
#include <set>
#include <queue>
#include <unordered_set>
#include <string>

#include "cell.hpp"
#include "coordinate.hpp"
#include "cellContract.hpp"
using namespace std;
namespace cz::lastaapps::vimxel::table {

enum class CellContentType {EMPTY, TEXT, ESCAPED, EXPRESSION};
using CT = table::CellContentType;

class Table final {
   private:
	unordered_map<Coordinates, unique_ptr<const Cell>> mMap;
	EmptyCell emptyCell;
	vector<shared_ptr<CellContract>> mContracts;
	bool mChanged = false;
	unordered_multimap<Coordinates, Coordinates> mDependencies, mDependenciesInversed;

   public:
	Table() = default;
	Table(const Table& other) = delete;
	Table(const Table&& other) = delete;
	Table& operator=(const Table& other) = delete;
	const Cell& getCell(const Coordinates& coord) const;
	void updateCell(const Coordinates& coord, const string& content);
	void deleteCell(const Coordinates& coord);

	shared_ptr<CellContract> createCellContract();

	Coordinates tableSize() const;
	bool isEmpty() const;
	void eraseAll();
	bool changed() const;
	void clearChanged();

private:
	void updateCellWithResult(const Coordinates& coord, SSingleTerm term);
	void updateCellAll(const Coordinates& coord, const string& content, SSingleTerm term);
	void updateCellInCycle(const Coordinates& coord, bool inCycle);
	bool isCellInCycle(const Coordinates& coord) const;
	bool tryParseNumber(const string& src, long double& out);

	void destroyOldCell(const Coordinates& coord);
	void onTextCellUpdated(const Coordinates& coord, const string& content);
	void onExpressionCellUpdated(const Coordinates& coord, const string& content);
	void recalculate(const Coordinates& coord);

	// preparation
	void clearDependent(const Coordinates& coord);

	// execution plan
	struct ExecutionItem {
		size_t size;
		Coordinates coord;
		bool operator <(const ExecutionItem& other) const;
	};
	using ExecutionPlan = priority_queue<ExecutionItem>;
	using OrderMap = unordered_map<Coordinates, size_t>;
	using VisitedSet = unordered_set<Coordinates>;
	using CycleRootsSet = unordered_set<Coordinates>;
	struct ExecutionArgs {
		OrderMap order;
		VisitedSet visited;
		CycleRootsSet cycleRoots;
	};
	void createExecutionPlan(const Coordinates& coord, ExecutionPlan& order, CycleRootsSet& cycleRoots) const;
	void createExecutionPlanRecursive(
		 const Coordinates& coord, ExecutionArgs& args ,size_t depth) const;

	// evaluation
	void evaluate(ExecutionPlan& plan, const CycleRootsSet& cycleRoots);
	void evaluateCell(const Coordinates& coord, const CycleRootsSet& cycleRoots);
	bool checkDependOnCycle(const Coordinates& coord, const set<Coordinates>& depend) const;

	// cell dependencies
	void addDependencies(const Coordinates& coord, const set<Coordinates>& depend);
	void removeDependencies(const Coordinates& coord);

	CellContentType isExpression(const string& text) const;

	// --- Contracts ------------------------------------------
	void updateContracts(const Coordinates& coord);
};
}  // namespace cz::lastaapps::vimxel::table
#endif
