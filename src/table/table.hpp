#ifndef H_TABLE
#define H_TABLE
#include <algorithm>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "cell.hpp"
#include "cellContract.hpp"
#include "coordinate.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::table {

/**
 * @brief table is used as main app data storage, it stores all the cells data and values
 */
class Table final {
   private:
	/**
	 * @brief Contains all the cells
	 */
	unordered_map<Coordinates, unique_ptr<const Cell>> mMap;
	/**
	 * @brief Sort of a singleton so it does not have to be recreated every time
	 */
	EmptyCell emptyCell;
	/**
	 * @brief All the data listeners
	 */
	vector<shared_ptr<CellContract>> mContracts;
	/**
	 * @brief Flag idicating some cell has been changed
	 */
	bool mChanged = false;
	/**
	 * @brief Caches dependencies of cells on another cells and the otherway around to make deletion easier
	 */
	unordered_multimap<Coordinates, Coordinates> mDependencies, mDependenciesInversed;

   public:
	Table() = default;
	Table(const Table& other) = delete;
	Table(const Table&& other) = delete;
	Table& operator=(const Table& other) = delete;

	/**
	 * @brief Result of updateCell operation
	 * if update succedd, success is true and message is undefined
	 * if update failed, success is false and there is an error message in the message field
	 */
	struct TableUpdateResult {
		bool success = false;
		string message;
	};

	/**
	 * @brief Get the Cell object for position given
	 *
	 * @param coord position of the cell
	 * @return cell on the position
	 */
	const Cell& getCell(const Coordinates& coord) const;
	/**
	 * @brief Validates cell content and tries to set new content, recalculates dependency tree
	 *
	 * @param coord cell position
	 * @param content new cell content
	 * @return if insert succedd, cycle or expression errors are considered invalid
	 */
	TableUpdateResult updateCell(const Coordinates& coord, const string& content);
	/**
	 * @brief Deletes all the cells in the table
	 */
	void deleteAll();

	/**
	 * @brief Create a new Cell Contract, so another observer can register for data
	 *
	 * @return new contart to register for data in
	 */
	shared_ptr<CellContract> createCellContract();

	/**
	 * @brief Finds coordinates of the cell with content and highes coordinates
	 *
	 * @return table size
	 */
	Coordinates tableSize() const;
	/**
	 * @brief Checks if there is alteast one cell saved
	 *
	 * @return if table is empty
	 */
	bool isEmpty() const;
	/**
	 * @brief Table has changed from the time it was last saved/loaded
	 *
	 * @return true if some cell has been changed
	 */
	bool changed() const;
	/**
	 * @brief Table has just been saved/loaded - no change has been made yet
	 */
	void clearChanged();

   private:
	/**
	 * @brief Used durring cell type evaluation
	 */
	enum class CellContentType {
		// no content
		EMPTY,
		// just text
		TEXT,
		// text starting with ==
		ESCAPED,
		// expression starting with =
		EXPRESSION,
	};
	using CT = CellContentType;

	/**
	 * @brief deletes a cell at coordinates, updates dependent cells
	 *
	 * @param coord position of the cell to delete
	 */
	void deleteCell(const Coordinates& coord);

	/**
	 * @brief Changes just a cell value, not content
	 * For example when expression tree in re-evaluated
	 *
	 * @param coord position to change value at
	 * @param term new cell value
	 */
	void updateCellWithResult(const Coordinates& coord, SSingleTerm term);
	/**
	 * @brief Updates content and value of a cell, sets cycle flag to false
	 *
	 * @param coord cell postition
	 * @param content new cell content
	 * @param term new cell value
	 */
	void updateCellAll(const Coordinates& coord, const string& content, SSingleTerm term);
	/**
	 * @brief Sets cycle flag for a cell
	 *
	 * @param coord the position of the cell
	 * @param inCycle if cell is or is not in a cycle
	 */
	void updateCellInCycle(const Coordinates& coord, bool inCycle);
	/**
	 * @brief Checks if a cell is in cycle
	 *
	 * @param coord position of the cell
	 * @return true if cell is in cycle
	 */
	bool isCellInCycle(const Coordinates& coord) const;
	/**
	 * @brief Tries to interpret cell content as number in formats 1, 1.1, .1
	 *
	 * @param src string/content to parse
	 * @param out parsed number, may be changed even if false is returned
	 * @return true if text is parsed as a number, false if parsing failed
	 */
	bool tryParseNumber(const string& src, long double& out);

	/**
	 * @brief Clear all the info stored about a cell, most importantly dependencies
	 *
	 * @param coord position of the cell
	 */
	void destroyOldCell(const Coordinates& coord);
	/**
	 * @brief Called when a text cell has been updated
	 *
	 * @param coord position
	 * @param content new cell content
	 */
	void onTextCellUpdated(const Coordinates& coord, const string& content);
	/**
	 * @brief Called when a cell with expresion should be updated
	 *
	 * @param coord position of the cell
	 * @param content new content to parse
	 */
	void onExpressionCellUpdated(const Coordinates& coord, const string& content);
	/**
	 * @brief Recalculates value of a cell
	 *
	 * @param coord the cells position
	 */
	void recalculate(const Coordinates& coord);

	// preparation
	/**
	 * @brief Clears all the dependencies of a cell
	 *
	 * @param coord the position of the cell to clear
	 */
	void clearDependent(const Coordinates& coord);

	// execution plan
	/**
	 * @brief One evaluation step
	 */
	struct ExecutionItem {
		// position in execution graph
		size_t index;
		// where should be cell updated
		Coordinates coord;

		/**
		 * @brief Compares two execution items
		 *
		 * @param other other item to compare with
		 * @return true if index is smaller. On = coords < is used
		 */
		bool operator<(const ExecutionItem& other) const;
	};
	using ExecutionPlan = priority_queue<ExecutionItem>;
	using OrderMap = unordered_map<Coordinates, size_t>;
	using VisitedSet = unordered_set<Coordinates>;
	using CycleRootsSet = unordered_set<Coordinates>;
	/**
	 * @brief Arguments used while recursively preparing execution plan
	 */
	struct ExecutionArgs {
		// in which order should be items evalulated, e.g. longest path in execution graph
		OrderMap order;
		// currently visited nodes in current tree branch
		VisitedSet visited;
		// all the nodes, where cycle has been found (not all the items in cycle, just roots)
		CycleRootsSet cycleRoots;
	};
	/**
	 * @brief Create a Execution Plan, in which order should be items evaluated
	 *
	 * @param coord starting cell position
	 * @param order output with execution order
	 * @param cycleRoots all the cycleroots found
	 */
	void createExecutionPlan(const Coordinates& coord, ExecutionPlan& order, CycleRootsSet& cycleRoots) const;
	/**
	 * @brief Recursive implementation of creating execution plan
	 *
	 * @param coord currenty processed cell
	 * @param args recursion arguments
	 * @param depth position in execution graph
	 */
	void createExecutionPlanRecursive(
	    const Coordinates& coord, ExecutionArgs& args, size_t depth) const;

	// evaluation
	/**
	 * @brief Evaluates value of a cells according to the plan
	 *
	 * @param plan order of cells
	 * @param cycleRoots where we know cycles are
	 */
	void evaluate(ExecutionPlan& plan, const CycleRootsSet& cycleRoots);
	/**
	 * @brief Evaluates individual cell
	 *
	 * @param coord cell coordinates
	 * @param cycleRoots is checked against if cell is in cycle
	 */
	void evaluateCell(const Coordinates& coord, const CycleRootsSet& cycleRoots);
	/**
	 * @brief Checks if any cell the cell is dependent on is in cycle
	 *
	 * @param coord the cell to check
	 * @param depend cells dependencies
	 * @return true if a cycle was found
	 */
	bool checkDependOnCycle(const Coordinates& coord, const set<Coordinates>& depend) const;

	// cell dependencies
	/**
	 * @brief Adds cell dependencies into according containers
	 *
	 * @param coord cell to add dependencies for
	 * @param depend all the dependencies of the cell
	 */
	void addDependencies(const Coordinates& coord, const set<Coordinates>& depend);
	/**
	 * @brief Removes dependencies added in addDependencies()
	 *
	 * @param coord cell to remove dependencies for
	 */
	void removeDependencies(const Coordinates& coord);

	/**
	 * @brief
	 *
	 * @param text finds out what kind of cell will this text be used for
	 * @return according cell type
	 */
	CellContentType isExpression(const string& text) const;

	// --- Contracts ------------------------------------------
	/**
	 * @brief Notifies all the observers, that a cell has changed
	 *
	 * @param coord position of changed cell
	 */
	void updateContracts(const Coordinates& coord);
};
}  // namespace cz::lastaapps::vimxel::table
#endif
