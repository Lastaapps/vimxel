#ifndef CELL_H
#define CELL_H
#include <string>
#include "../expr/nodes/terms.hpp"
using namespace std;

namespace cz::lastaapps::vimxel::table {

using ST = shared_ptr<expr::Term>;
class Cell {
   public:
	virtual ~Cell() {}
	// real content
	virtual const string& getContent() const = 0;
	// value in table
	virtual string getValue() const = 0;
	// value for calculations
	virtual ST getTerm() const = 0;
	// cell in in a cycle
	virtual bool isInCycle() const = 0;

	virtual Cell* clone() const = 0;

	protected:
};

const static auto EMPTY_TERM = make_shared<expr::DoubleTerm>(0.0L);

class TextCell final : public Cell {
 private:
	string mContent;
	ST mTerm;
	bool mInCycle;
   public:
	TextCell(string, ST term, bool inCycle);
    ~TextCell() = default;
	const string& getContent() const override;
	string getValue() const override;
	ST getTerm() const override;
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
	ST getTerm() const override;
	bool isInCycle() const override;
	virtual Cell* clone() const override;
};

}  // namespace cz::lastaapps::vimexel::table
#endif