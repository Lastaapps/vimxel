#ifndef H_APP
#define H_APP
#include <ncurses.h>

#include <string>
#include <vector>

#include "display/display.hpp"
#include "table/table.hpp"
#include "vim/parserResult.hpp"

using namespace std;
namespace cz::lastaapps::vimxel {

using Res = vim::ParserResult;

struct FileLoadResult final {
	shared_ptr<table::Table> table;
	bool success = false;
	string message;
};

class App final {
	table::Coordinates mWindowSize;

   public:
	int run(vector<string> args);

   private:
	FileLoadResult loadTable(const string &filename);
	void printArgs(const vector<string> &args);
	void initNCurses();
	void destroyNCurses();
	void setupDisplay();
	bool checkWindowSize();
};
}  // namespace cz::lastaapps::vimxel

#endif