#include "state.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::display {

void State::setPosition(const table::Coordinates& coord) {
    if (coord != mPos) {
		mPos = coord;
		notifyPos();
	}
}
void State::moveX(bool down) {
	setPosition(down ? mPos.incX() : mPos.decX());
}
void State::moveY(bool right) {
	setPosition(right ? mPos.incY() : mPos.decY());
}

void State::setViewPort(const table::Coordinates& coord) {
    if (coord != mViewPort) {
		mViewPort = coord;
		notifyViewPort();
	}
}
void State::moveViewX(bool down) {
	setViewPort(down ? mViewPort.incX() : mViewPort.decX());
}
void State::moveViewY(bool right) {
	setViewPort(right ? mViewPort.incY() : mViewPort.decY());
}

void State::notifyPos() {
    for (auto itr = mCallbacks.begin(); itr != mCallbacks.end(); itr++) {
        if (itr -> use_count() == 1)
            itr = mCallbacks.erase(itr);
        else
            (**itr).onUpdatePos(mPos);
    }
}
void State::notifyViewPort() {
    for (auto itr = mCallbacks.begin(); itr != mCallbacks.end(); itr++) {
        if (itr -> use_count() == 1)
            itr = mCallbacks.erase(itr);
        else
            (**itr).onUpdateViewPort(mViewPort);
    }
}

void State::registerCallback(shared_ptr<StateCallback> call) {
    call -> onUpdatePos(mPos);
    call -> onUpdateViewPort(mViewPort);
    mCallbacks.emplace_back(call);
}
}
