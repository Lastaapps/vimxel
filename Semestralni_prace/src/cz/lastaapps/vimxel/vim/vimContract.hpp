#ifndef H_VIM_CONTRACT
#define H_VIM_CONTRACT
#include "mode.hpp"
#include <functional>
#include <memory>
#include <string>

using namespace std;
namespace cz::lastaapps::vimxel::vim {

struct VimInfo final {
    size_t cursorPos;
    string text;
    Mode mode;
    VimInfo();
    VimInfo(size_t cP, const string & s, Mode m);
};

class VimContract final {
    using Callback = function<void(const VimInfo&)>;
    bool hasCallback = false;
    Callback mCallback;
    public:
    void onDataChanged(const VimInfo& info);
    void registerCallback(Callback c);
    void unregisterCallback();
};
}  // namespace cz::lastaapps::vimxel::vim

#endif