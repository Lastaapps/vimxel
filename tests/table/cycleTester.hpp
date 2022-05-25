#pragma once

#include <cassert>
#include <iostream>

#include "../..//src/table/table.hpp"
#include "../testUtils.hpp"

using namespace std;
using namespace cz::lastaapps::vimxel;

namespace cz::lastaapps::vimxel::table {

/**
 * @brief Tests that cycles cannot be inserted into a table
 */
struct CycleTester final {
	void operator()();

   private:
	void insertComplexCycle();
	void insertSelfCycle();
};

}  // namespace cz::lastaapps::vimxel::table