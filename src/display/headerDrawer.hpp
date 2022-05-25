#ifndef H_HEADER_DRAWER
#define H_HEADER_DRAWER
#include <ncurses.h>

#include "../table/coordinate.hpp"
#include "drawer.hpp"

using namespace std;
using namespace cz::lastaapps::vimxel;
namespace cz::lastaapps::vimxel::display {
/**
 * @brief Draws header in top left corner
 */
class HeaderDrawer final : public Drawer {
   public:
	/**
	 * @brief Construct a new Header Drawer object
	 *
	 * @param w windows to draw into
	 */
	HeaderDrawer(WINDOW* w);
	/**
	 * @brief Draws VimXel
	 */
	void draw() override;
};
}  // namespace cz::lastaapps::vimxel::display
#endif