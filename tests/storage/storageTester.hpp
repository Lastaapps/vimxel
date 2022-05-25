#pragma once

#include <cassert>
#include <iostream>

#include "../../src/storage/storage.hpp"
#include "../testUtils.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::storage {

/**
 * @brief Tests csv ;"\n escaping and parsing back
 */
struct StorageTester final {
	using S = Storage;

	void operator()();

   private:
	void testEscape();
	void testDecode();
	void testBoth();
	string incStr(string str);
	inline string impEsc(const string& str);
};
}