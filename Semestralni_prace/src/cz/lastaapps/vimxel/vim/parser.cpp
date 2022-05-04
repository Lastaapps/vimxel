#include "parser.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {

void Parser::VimStateCallback::onUpdatePos(const table::Coordinates& coord) {
	mParent->setPos(coord);
}

Parser::Parser(
    shared_ptr<display::State> state,
    shared_ptr<table::Table> table,
    const vector<string> args)
    : mDisplayState(state), mTable(table), mArgs(args) {

	mDisplayStateCallback = shared_ptr<display::StateCallback>(new VimStateCallback(this));
	mDisplayState->registerCallback(mDisplayStateCallback);
}

ParserResult Parser::handleKeyBoard() {
	using Res = ParserResult;
	int ch = getch();
	if (ch == ERR) return Res::NOPE;
	if (ch == 'q') return Res::QUIT;
	switch (ch) {
	case 'k':
		mDisplayState->moveY(false);
		break;
	case 'j':
		mDisplayState->moveY(true);
		break;
	case 'h':
		mDisplayState->moveX(false);
		break;
	case 'l':
		mDisplayState->moveX(true);
		break;
	case KEY_UP:
		mDisplayState->moveViewY(false);
		break;
	case KEY_DOWN:
		mDisplayState->moveViewY(true);
		break;
	case KEY_LEFT:
		mDisplayState->moveViewX(false);
		break;
	case KEY_RIGHT:
		mDisplayState->moveViewX(true);
		break;
	case 'r':
		notifyContracts(VimInfo(0, "ahojky", Mode::COMMAND));
		break;
	case 't':
		notifyContracts(VimInfo(3, "no nazdar", Mode::NORMAL));
		break;
	default:
		return Res::UNKNOWN;
	}
	return Res::FINE;
}

shared_ptr<VimContract> Parser::createContract() {
	auto newCnt = shared_ptr<VimContract>(new VimContract());
	mContracts.push_back(newCnt);
	return newCnt;
}
void Parser::notifyContracts(const VimInfo& info) {
	for (auto itr = mContracts.begin(); itr != mContracts.end(); itr++) {
		if (itr -> use_count() == 1)
			itr = mContracts.erase(itr);
		else
			(*itr)->onDataChanged(info);
	}
}

void Parser::setPos(const table::Coordinates& coord) { mPos = coord; }
}  // namespace cz::lastaapps::vimxel::vim