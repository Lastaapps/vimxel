#ifndef H_STRING_UTILS
#define H_STRING_UTILS
#include <algorithm>
#include <string>

using namespace std;
namespace cz::lastaapps::vimxel {
/**
 * Functions for string manipulation
 */

/**
 * @brief Trim spaces from the start of a string
 *
 * @param s string to trim
 */
inline void ltrim(std::string &s) {
	s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
		        return !std::isspace(ch);
	        }));
}
/**
 * @brief Trim spaces from the end of a string
 *
 * @param s string to trim
 */
inline void rtrim(std::string &s) {
	s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
		        return !std::isspace(ch);
	        }).base(),
	        s.end());
}
/**
 * @brief Trim spaces at the beginning and end of a string
 *
 * @param s string to trim
 */
inline void trim(std::string &s) {
	ltrim(s);
	rtrim(s);
}

}  // namespace cz::lastaapps::vimxel

#endif