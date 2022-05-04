#ifndef H_STRING_UTILS
#define H_STRING_UTILS
#include <algorithm>
#include <string>

using namespace std;
namespace cz::lastaapps::vimxel {

inline void ltrim(std::string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

inline void rtrim(std::string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}
 
} // namespace cz::lastaapps::vimxel

#endif