#ifndef H_ABS_PARSER
#define H_ABS_PARSER
#include <string>
#include "parserResult.hpp"
#include "mode.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::vim {
class AbsParser  {
    public:
    virtual ~AbsParser() = default;
    virtual ParserResult handleKey(Mode & outMode) = 0;
    virtual pair<string, size_t> getTextAndPosition() = 0;
};
}

#endif