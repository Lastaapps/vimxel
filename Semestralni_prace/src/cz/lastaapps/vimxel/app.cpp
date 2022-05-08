#include "app.hpp"
#include "log.hpp"
#include "table/cell.hpp"
#include "display/state.hpp"
#include "display/display.hpp"
#include "storage/storage.hpp"
#include "vim/vimParser.hpp"
#include <thread>

namespace cz::lastaapps::vimxel {
int App::run(vector<string> args) {
	log("App started");
	printArgs(args);
	string filename = args.size() >= 2 ? args[1] : "";
	initNCurses();
    try {
		log("Loading data");
		shared_ptr<table::Table> table = loadTable(filename);
		shared_ptr<table::CellContract> cellContract = table->createCellContract();
		shared_ptr<display::State> dState = make_shared<display::State>();

		log("Staring parser");
		vim::VimParser vim(dState, table, filename);
		shared_ptr<vim::VimContract> vimContract = vim.createContract();

		log("Setting up display");
		display::Display display(dState, cellContract, vimContract);

		while(true) {
			if (checkWindowSize()) {
				display.recreate();
				display.draw();
			}
			vim::Res res = vim.handleKeyBoard();
			if (res == vim::Res::QUIT) break;
			this_thread::sleep_for(10ms);
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

shared_ptr<table::Table> App::loadTable(const string &filename) {
    auto table = shared_ptr<table::Table>(new table::Table);
	if (!filename.empty())
		storage::Storage::loadData(filename, table);
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

bool App::checkWindowSize() {
	size_t y, x;
	getmaxyx(stdscr, y, x);
	if (mWindowSize.x() != x || mWindowSize.y() != y) {
		mWindowSize = Coordinates(x, y);
		mlog << "New screen size: " << mWindowSize << endl;
		return true;
	}
	return false;
}

}  // namespace cz::lastaapps::vimxel