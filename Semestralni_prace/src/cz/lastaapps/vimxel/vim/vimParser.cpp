#include "vimParser.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {

void VimParser::VimStateCallback::onUpdatePos(const table::Coordinates& coord) {
	mParent->setPos(coord);
}
void VimParser::VimStateCallback::onUpdateViewPort(const table::Coordinates& coord) {
	mParent->setViewPort(coord);
}

VimParser::VimParser(
    shared_ptr<display::State> state,
    shared_ptr<table::Table> table,
    const vector<string> args)
    : mState(VimState(state, table, args)) {
	mDisplayStateCallback = shared_ptr<display::StateCallback>(new VimStateCallback(this));
	mState.mDisplayState->registerCallback(mDisplayStateCallback);

	updateInfo();
}

ParserResult VimParser::handleKeyBoard() {
	ParserResult res = getParser().handleKey(mMode);
	if (res == ParserResult::UNKNOWN)
		unknowsInfo();
	else updateInfo();
	return res;
}

shared_ptr<VimContract> VimParser::createContract() {
	auto newCnt = shared_ptr<VimContract>(new VimContract());
	mContracts.push_back(newCnt);
	updateInfo();
	return newCnt;
}
void VimParser::notifyContracts(const VimInfo& info) {
	for (auto itr = mContracts.begin(); itr != mContracts.end(); itr++) {
		if (itr->use_count() == 1)
			itr = mContracts.erase(itr);
		else
			(*itr)->onDataChanged(info);
	}
}

AbsParser& VimParser::getParser() {
	switch (mMode) {
	case Mode::NORMAL:
		return normalParser;
	case Mode::COMMAND:
		return commandParser;
	case Mode::INSERT:
		return insertParser;
	default:
		throw runtime_error("Unknown mode");
	}
}

void VimParser::updateInfo() {
	auto textInfo = getParser().getTextAndPosition();
	VimInfo info(textInfo.second, textInfo.first, mMode);
	notifyContracts(info);
}
void VimParser::unknowsInfo() {
	VimInfo info(-1, "Unknow command or key sequence", mMode);
	notifyContracts(info);
}

void VimParser::setPos(const table::Coordinates& coord) {
	mState.mPos = coord;
	updateInfo();
}
void VimParser::setViewPort(const table::Coordinates& coord) {
	mState.mViewPort = coord;
	updateInfo();
}
}  // namespace cz::lastaapps::vimxel::vim