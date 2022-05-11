#ifndef H_STATE
#define H_STATE
#include <list>
#include <memory>

#include "../table/coordinate.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::display {

/**
 * @brief Used in State to update observers
 */
struct StateCallback {
	virtual ~StateCallback() = default;
	virtual void onUpdatePos(const table::Coordinates& pos) = 0;
	virtual void onUpdateViewPort(const table::Coordinates& coord) = 0;
};

/**
 * @brief Represents the state display is in
 */
class State final {
	/**
	 * @brief selected position
	 */
	table::Coordinates mPos;
	/**
	 * @brief current viewPort
	 */
	table::Coordinates mViewPort;
	/**
	 * @brief Callbacks back to data observers
	 */
	list<shared_ptr<StateCallback>> mCallbacks;

   public:
	/**
	 * @brief Set selected potion and updates observers
	 * Also updates viewport if selected cell wouldn't be visible
	 * @param coord new selected position
	 */
	void setPosition(const table::Coordinates& coord);
	/**
	 * @brief Moves selected cell vertically when possible
	 * @param down moves down it true
	 */
	void moveX(const bool down);
	/**
	 * @brief Moves selected cell horizontally when possible
	 * @param right moves right it true
	 */
	void moveY(const bool right);
	/**
	 * @brief Set new viewport
	 * @param coord new viewport
	 */
	void setViewPort(const table::Coordinates& coord);
	/**
	 * @brief moves viewport vertically if possible
	 * @param down moves down if true, left otherwise
	 */
	void moveViewX(const bool down);
	/**
	 * @brief moves viewport horizontally if possible
	 * @param right moves right if true, left otherwise
	 */
	void moveViewY(const bool right);

	/**
	 * @brief registers new callback
	 * callback are automatically unlisted
	 * @param call callback to register
	 */
	void registerCallback(shared_ptr<StateCallback> call);

   private:
	/**
	 * @brief Tells observers that position has changed
	 */
	void notifyPos();
	/**
	 * @brief Tells observers that viewport has changed
	 */
	void notifyViewPort();
};
}  // namespace cz::lastaapps::vimxel::display

#endif