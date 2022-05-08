#ifndef APP_H
#define APP_H
#include <ncurses.h>

#include <string>
#include <vector>

#include "vim/parserResult.hpp"
#include "display/display.hpp"
#include "table/table.hpp"

using namespace std;
namespace cz::lastaapps::vimxel {
using Res = vim::ParserResult;
class App final {
	  table::Coordinates mWindowSize;
   public:
	int run(vector<string> args);

   private:
	shared_ptr<table::Table> loadTable(const string &filename);
	void printArgs(const vector<string> &args);
	void initNCurses();
	void destroyNCurses();
	void setupDisplay();
	bool checkWindowSize();

	// Storage engine
	// Vim
};

}  // namespace cz::lastaapps::vimxel

#endif