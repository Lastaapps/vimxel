#ifndef CELL_H
#define CELL_H
#include <string>
using namespace std;

namespace cz::lastaapps::vimxel::table {

class Cell {
   public:
	virtual ~Cell() {}
	virtual const string& getContent() const = 0;
	virtual Cell* clone() const = 0;
};

class TextCell : public Cell {
 private:
	string mContent;
   public:
	TextCell(string);
    ~TextCell() = default;
	const string& getContent() const override;
	virtual Cell* clone() const override;
};

class EmptyCell : public Cell {
 private:
	string emptyString = "";
   public:
    ~EmptyCell() = default;
	const string& getContent() const override;
	virtual Cell* clone() const override;
};

}  // namespace cz::lastaapps::vimexel::table
#endif