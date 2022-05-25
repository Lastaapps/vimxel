#ifndef H_VIM_CONTRACT
#define H_VIM_CONTRACT

#include <functional>
#include <memory>
#include <string>

#include "mode.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {

/**
 * @brief Informs UI about current text, cursor and mode properties
 */
struct VimInfo final {
	/**
	 * @brief Represents cursor position in text. -1 means cursor is disabled
	 */
	size_t cursorPos;
	/**
	 * @brief The text to show
	 */
	string text;
	/**
	 * @brief Current mode
	 */
	Mode mode;

	/**
	 * @brief Construct a new Vim Info object
	 */
	VimInfo();
	/**
	 * @brief Construct a new Vim Info object
	 *
	 * @param cP same as cursorPos
	 * @param s same as text
	 * @param m same as mode
	 */
	VimInfo(size_t cP, const string& s, Mode m);
};

/**
 * @brief Provides VimInfo to other app components
 */
class VimContract final {
	// callback to call on update
	using Callback = function<void(const VimInfo&)>;
	bool mHasCallback = false;
	Callback mCallback;

	// chache of the latest info
	VimInfo mLatest;

   public:
	/**
	 * @brief Changes cache and notifies observer
	 *
	 * @param info data to send to an observer
	 */
	void onDataChanged(const VimInfo& info);
	/**
	 * @brief Registreas new callback, replaces the old one, cache is send immediately
	 *
	 * @param c callback to register
	 */
	void registerCallback(Callback c);
	/**
	 * @brief Unregisters the current callback
	 *
	 * @param c callback to register
	 */
	void unregisterCallback();
};
}  // namespace cz::lastaapps::vimxel::vim

#endif