#ifndef H_CELL
#define H_CELL
#include <string>
#include "../expr/nodes/terms.hpp"
using namespace std;

namespace cz::lastaapps::vimxel::table {
using STerm = shared_ptr<expr::Term>;
using SSingleTerm = shared_ptr<expr::SingleTerm>;

class Cell {
   public:
	virtual ~Cell() {}
	// real content
	virtual const string& getContent() const = 0;
	// value in table
	virtual string getValue() const = 0;
	// value for calculations
	virtual SSingleTerm getTerm() const = 0;
	// cell in in a cycle
	virtual bool isInCycle() const = 0;

	virtual Cell* clone() const = 0;

	protected:
};

const static auto EMPTY_TERM = make_shared<expr::DoubleTerm>(0.0L);

class TextCell final : public Cell {
 private:
	string mContent;
	SSingleTerm mTerm;
	bool mInCycle;
   public:
	TextCell(string, SSingleTerm term, bool inCycle);
    ~TextCell() = default;
	const string& getContent() const override;
	string getValue() const override;
	SSingleTerm getTerm() const override;
	bool isInCycle() const override;
	virtual Cell* clone() const override;
};

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

}  // namespace cz::lastaapps::vimexel::table
#endif