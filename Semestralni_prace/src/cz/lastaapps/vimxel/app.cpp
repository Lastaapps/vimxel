#include "app.hpp"
#include "log.hpp"
#include "table/cell.hpp"
#include "display/state.hpp"
#include "display/display.hpp"
#include "storage/storage.hpp"
#include "vim/parser.hpp"

namespace cz::lastaapps::vimxel {
int App::run(vector<string> args) {
	log("App started");
	printArgs(args);
	initNCurses();
    try {
		log("Loading data");
		shared_ptr<table::Table> table = loadTable(args);
		shared_ptr<display::State> dState = make_shared<display::State>();

		log("Setting up display");
		display::Display display(dState, table->createCellContract());
        display.draw();

		log("Staring parser");
		vim::Parser vim(dState, table, args);
		while(true) {
			using Res = vim::ParserResult;
			Res res = vim.handleKeyBoard();
			if (res == Res::QUIT) break;
		}
	} catch (const std::exception& ex) {
		destroyNCurses();
		log("Exception in app: "s + ex.what());
		cerr << ex.what() << endl;
		return 1;
	} catch (const std::string& ex) {
		destroyNCurses();
		log("Exception in app: "s + ex);
		cerr << ex << endl;
		return 1;
	} catch (...) {
		destroyNCurses();
		log("Exception in app");
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
	clear();
	refresh();
	endwin();
}

}  // namespace cz::lastaapps::vimxel