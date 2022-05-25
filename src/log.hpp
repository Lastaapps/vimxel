#ifndef H_LOG
#define H_LOG
#include <fstream>

using namespace std;

namespace cz::lastaapps::vimxel {

/**
 * @brief Name of the default log file
 */
static string LOG_FILE_NAME = "logs.txt";
/**
 * @brief Global logger, logs into file defined in LOG_FILE_NAME
 */
extern ofstream mlog;

/**
 * @brief Logs string into mlog stream ending with new line
 *
 * @param str text to log
 */
inline void log(const string str) {
	mlog << str << endl;
}
}  // namespace cz::lastaapps::vimxel

#endif