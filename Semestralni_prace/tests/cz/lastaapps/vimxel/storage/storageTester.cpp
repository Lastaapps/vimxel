#include "../../../../../src/cz/lastaapps/vimxel/storage/storage.hpp"
#include "../testUtils.hpp"
#include <cassert>
#include <iostream>

using namespace std;
namespace cz::lastaapps::vimxel::storage {

struct StorageTester final {
	void operator()() {
        cout << "Testing storage" << endl;
        testEscape();
        testDecode();
        testBoth();
    }

private:
	using S = Storage;
    void testEscape() {
        assPr(S::escapeText(""), ""s);
        assPr(S::escapeText("a"), "a"s);
        assPr(S::escapeText("a;"), "\"a;\""s);
        assPr(S::escapeText("a;h"), "\"a;h\""s);
        assPr(S::escapeText("a\nh"), "\"a\nh\""s);
        assPr(S::escapeText("\""), "\"\"\"\""s);
        assPr(S::escapeText("\"\""), "\"\"\"\"\"\""s);
        assPr(S::escapeText("\";"), "\"\"\";\""s);
        assPr(S::escapeText("\";\""), "\"\"\";\"\"\""s);
    }

    void testDecode() {
        assPr(S::importText(""), ""s);
        assPr(S::importText("a"), "a"s);
        assPr(S::importText("a;"), "a"s);
        assPr(S::importText("a\n"), "a"s);
        assPr(S::importText("\";\""), ";"s);
        assPr(S::importText("\";\";"), ";"s);
        assPr(S::importText("\";\"\";\""), ";\";"s);
        assPr(S::importText("\"\"\"\"\"\"\"\"\"\""), "\"\"\"\""s);
        assPr(S::importText("\"\"\"\"\"\";"), "\"\""s);

        shouldThrow(S::importText("\""));
        shouldThrow(S::importText("\"a"));
        shouldThrow(S::importText("\";"));
        shouldThrow(S::importText("\"a\"a\""));
        shouldThrow(S::importText("\"\"\""));
    }

    void testBoth() {
        string str = "";
        for (size_t t = 0; t < 10000; t++) {
            assPrMsg(str + " '" + S::escapeText(str) + "'", impEsc(str), str);
            str = move(incStr(str));
        }
    }

	string incStr(string str) {
		for (size_t i = str.size(); i > 0; i--) {
			uint8_t c = str.at(i - 1);
			if (c != 'Z') {
				str.at(i - 1) = c + 1;
				return str;
			} else {
				str.at(i - 1) = '\n';
			}
		}
		str = 'A' + str;
		return str;
	}

    inline string impEsc(const string & str) {
        return S::importText(S::escapeText(str));
    }
};

}