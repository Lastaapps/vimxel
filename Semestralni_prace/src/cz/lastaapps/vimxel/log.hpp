#ifndef H_LOG
#define H_LOG
#include <fstream>

using namespace std;
namespace cz::lastaapps::vimxel {
static string LOG_FILE_NAME = "logs.txt";
extern ofstream mlog;

inline void log(const string str) {
    mlog << str << endl;
}
}

#endif