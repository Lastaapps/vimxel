#include "app.hpp"
#include "table/cell.hpp"

namespace cz::lastaapps::vimxel {
int App::run(vector<string> args) {
    initNCurses();
    try {
		shared_ptr<table::Table> table = loadTable();
		display::Display display(table->createCellContract());
        display.draw();
	} catch(...) {
		destroyNCurses();
		return 1;
	}
    destroyNCurses();
	return 0;
}

shared_ptr<table::Table> App::loadTable() {
    auto table = shared_ptr<table::Table>(new table::Table);
	for (int i = 0; i < 42; i++)
		for (int j = 0; j < 69; j++)
			table->updateCell(Coordinates(i, j), TextCell(to_string(i + 1) + ", " + to_string(j + 1)));
	return table;
}

void App::initNCurses() {
	initscr();
	//  Ctr+C gets ignored
	// raw();
	//  Ctr+C works as normal
	cbreak();
	// pressed characters wouldn't be printed
	noecho();
	// arrows, F keys and others enabled
	keypad(stdscr, TRUE);
	// hide cursor
	curs_set(false);
}

void App::destroyNCurses() {
	endwin();
}

}  // namespace cz::lastaapps::vimxel