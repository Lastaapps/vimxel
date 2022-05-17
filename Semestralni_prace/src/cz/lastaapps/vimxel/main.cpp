#include <string>
#include <vector>

#include "app.hpp"

using namespace std;

/**
 * @brief Starts the program
 * 
 * @param cnt number of comandline args
 * @param args command line args + executable file name
 * @return int program result code
 */
int main(int cnt, char** args) {
	vector<string> normal;
	for (int i = 0; i < cnt; i++) {
		normal.emplace_back(string(args[i]));
	}
	cz::lastaapps::vimxel::App().run(normal);
	return 0;
}
