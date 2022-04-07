#include <cassert>
#include <iostream>
#include <string>

using namespace std;
namespace cz::lastaapps::vimxel {

#define assPr(a, b) assert(printIfDiffer("Mismatch"s, (a), (b)));
#define assPrMsg(s, a, b) assert(printIfDiffer((s), (a), (b)));

template <typename T>
bool printIfDiffer(const string & message, const T& t1, const T& t2) {
	if (t1 != t2) {
		cout << message << ": " << t1 << " x " << t2 << endl;
		return false;
	}
	return true;
}

template <typename T>
const T& pr(const T& any) {
	cout << any << endl;
	return any;
}
template <typename T>
T& pr(T& any) {
	cout << any << endl;
	return any;
}
template <typename T>
const T& pr(const string& message, const T& any) {
	cout << message << ": " << any << endl;
	return any;
}
template <typename T>
T& pr(const string& message, T& any) {
	cout << message << ": " << any << endl;
	return any;
}
}  // namespace cz::lastaapps::vimxel