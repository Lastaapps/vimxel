#include "app.hpp"
#include <vector>
#include <string>
using namespace std;

int main(int cnt, char** args) {
	vector<string> normal;
	for (int i = 0; i < cnt; i++) {
		normal.emplace_back(string(args[i]));
	}
	cz::lastaapps::vimxel::App().run(normal);
	return 0;
}
