#ifndef H_STATE
#define H_STATE
#include "../table/coordinate.hpp"
#include <memory>
#include <list>

using namespace std;
namespace cz::lastaapps::vimxel::display {

struct StateCallback {
    virtual ~StateCallback() = default;
    virtual void onUpdatePos(const table::Coordinates& pos) = 0;
    virtual void onUpdateViewPort(const table::Coordinates& coord) = 0;
};

class State final {
    table::Coordinates mPos;
    table::Coordinates mViewPort;
    list<shared_ptr<StateCallback>> mCallbacks;

    public:
	void setPosition(const table::Coordinates& corrd);
	void moveX(bool down);
	void moveY(bool right);
	void setViewPort(const table::Coordinates& corrd);
	void moveViewX(bool down);
	void moveViewY(bool right);

    void registerCallback(shared_ptr<StateCallback> call);
    private:
    void notifyPos();
    void notifyViewPort();
};
}

#endif