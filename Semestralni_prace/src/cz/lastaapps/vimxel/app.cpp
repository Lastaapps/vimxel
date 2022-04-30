#include "app.hpp"
#include "log.hpp"
#include "table/cell.hpp"
#include "storage/storage.hpp"

namespace cz::lastaapps::vimxel {
int App::run(vector<string> args) {
	printArgs(args);
	initNCurses();
    try {
		shared_ptr<table::Table> table = loadTable(args);
		display::Display display(table->createCellContract());
        display.draw();
	} catch (const std::exception& ex) {
		destroyNCurses();
		cerr << ex.what() << endl;
		return 1;
	} catch (const std::string& ex) {
		destroyNCurses();
		cerr << ex << endl;
		return 1;
	} catch (...) {
		destroyNCurses();
		cerr << "Unknown exception" << endl;
		return 1;
	}
	destroyNCurses();
	return 0;
}

void App::printArgs(const vector<string> &args) {
	mlog << "App args: ";
	bool isFirst = true;
	for (const auto& arg : args) {
		if (isFirst)
			isFirst = false;
		else
			mlog << ", ";
		mlog << arg;
	}
	mlog << endl;
}

shared_ptr<table::Table> App::loadTable(const vector<string> &args) {
    auto table = shared_ptr<table::Table>(new table::Table);
	if (args.size() >= 2)
		storage::Storage::loadData(args.at(1), table);
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