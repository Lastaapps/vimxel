#ifndef H_VIM_DRAWER
#define H_VIM_DRAWER
#include <ncurses.h>

#include <memory>

#include "../vim/vimContract.hpp"
#include "drawer.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::display {

/**
 * @brief Draws bottom vim bar
 */
class VimDrawer final : public Drawer {
   private:
	// data provider
	shared_ptr<vim::VimContract> mContract;
	// current state
	vim::VimInfo mInfo;

   public:
	/**
	 * @brief Construct a new Vim Drawer object
	 *
	 * @param w window to write into
	 * @param contract data source
	 */
	VimDrawer(WINDOW* w, shared_ptr<vim::VimContract> contract);
	/**
	 * @brief Draws content
	 */
	void draw() override;

   private:
	/**
	 * @brief Replaces and redraws according to new info
	 * @param info new bar state
	 */
	void updateInfo(const vim::VimInfo& info);
};
}  // namespace cz::lastaapps::vimxel::display

#endif