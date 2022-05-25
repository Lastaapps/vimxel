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

/**
 * @brief Mannages app lifecycle, loads default data, connects components
 * and manages screen resolution changes
 */
class App final {
	table::Coordinates mWindowSize;

   public:
	/**
	 * @brief Starts the app
	 *
	 * @param args commandline args
	 * @return int program result code
	 */
	int run(const vector<string> &args);

   private:
	/**
	 * @brief Datacarrier for loadTable() method
	 */
	struct FileLoadResult final {
		const shared_ptr<table::Table> table;
		const bool success = false;
		const string message;
	};

	/**
	 * @brief Try to load first data according to comandline args
	 *
	 * @param filename file to load
	 * @return true if loading succeed
	 */
	FileLoadResult loadTable(const string &filename);
	/**
	 * @brief initializes ncurses
	 */
	void initNCurses();
	/**
	 * @brief ends ncurses
	 */
	void destroyNCurses();
	/**
	 * @brief creates/recreates display object according to current screen size
	 */
	void setupDisplay();
	/**
	 * @brief Checks if terminal size changed
	 *
	 * @return true if size changed
	 */
	bool checkWindowSize();
};
}  // namespace cz::lastaapps::vimxel

#endif