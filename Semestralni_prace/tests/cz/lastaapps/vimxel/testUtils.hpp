#pragma once

#include <cassert>
#include <iostream>
#include <string>

using namespace std;
namespace cz::lastaapps::vimxel {

/*void printEscapeSpecial(ostream & out, const string & str) {
    for (auto it = str.begin(); it != str.end(); it++) {
        const char c = *it;
        switch(c) {
            case '\n': out << "\\n";
                break;
            case '\t': out << "\\t";
                break;
            default: out << c;
        }
    }
}

bool printIfDiffer(const string & message, const string& t1, const string& t2) {
    if (t1 != t2) {
        printEscapeSpecial(cout, message);
        cout << ": ";
        printEscapeSpecial(cout, t1);
        cout << " x ";
        printEscapeSpecial(cout, t2);
        cout << endl;
        return false;
    }
    return true;
}*/

template <typename T>
bool printIfDiffer(const string& message, const T& t1, const T& t2) {
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

#define assPr(a, b) assert(printIfDiffer("Mismatch"s, (a), (b)));
#define assPrMsg(s, a, b) assert(printIfDiffer((s), (a), (b)));

#define shouldThrow(a) \
	try {              \
		a;             \
		assert(false); \
	} catch (...) {    \
	}

}  // namespace cz::lastaapps::vimxel