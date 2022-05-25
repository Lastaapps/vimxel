#ifndef H_CELL
#define H_CELL
#include <string>

#include "../expr/nodes/terms.hpp"
using namespace std;

namespace cz::lastaapps::vimxel::table {

using STerm = shared_ptr<expr::Term>;
using SSingleTerm = shared_ptr<expr::SingleTerm>;

/**
 * @brief Represents a cell of a table
 *
 */
class Cell {
   public:
	virtual ~Cell() {}
	/**
	 * @brief Gets real content, what user has written
	 *
	 * @return cell content
	 */
	virtual const string& getContent() const = 0;
	/**
	 * @brief Get calculated value of the cell, but in string form
	 *
	 * @return cell value string
	 */
	virtual string getValue() const = 0;
	/**
	 * @brief Get calculated value of the cell
	 *
	 * @return cell value term
	 */
	virtual SSingleTerm getTerm() const = 0;
	/**
	 * @brief Checks if the cell is in or depends on a cycle
	 *
	 * @return true if the cell is in a cycle
	 */
	virtual bool isInCycle() const = 0;

	/**
	 * @brief Creates new copy of cell object
	 *
	 * @return new copy
	 */
	virtual Cell* clone() const = 0;
};

// just to save memory
const static auto EMPTY_TERM = make_shared<expr::DoubleTerm>(0.0L);

/**
 * @brief Normal cell with content in it of any type
 */
class TextCell final : public Cell {
   private:
	// user entered content
	string mContent;
	// value
	SSingleTerm mTerm;
	// if the cell is in a cycle
	bool mInCycle;

   public:
	/**
	 * @brief Construct a new Text Cell object
	 *
	 * @param content cell content
	 * @param term cell term
	 * @param inCycle is cell in cycle
	 */
	TextCell(string content, SSingleTerm term, bool inCycle);
	~TextCell() = default;

	const string& getContent() const override;
	string getValue() const override;
	SSingleTerm getTerm() const override;
	bool isInCycle() const override;
	virtual Cell* clone() const override;
};

/**
 * @brief Represents an empty cell
 * This one shouldn't be saved into data storage (no item in preffered)
 */
class EmptyCell final : public Cell {
   private:
	const string emptyString = "";

   public:
	~EmptyCell() = default;

	const string& getContent() const override;
	string getValue() const override;
	SSingleTerm getTerm() const override;
	bool isInCycle() const override;
	virtual Cell* clone() const override;
};

}  // namespace cz::lastaapps::vimxel::table
#endif