#pragma once

#include <cassert>
#include <iostream>

#include "../../src/table/coordinate.hpp"
#include "../testUtils.hpp"

using namespace std;
using namespace cz::lastaapps::vimxel;

namespace cz::lastaapps::vimxel::table {

/**
 * @brief Tests conversion from coordinates to human readable form and back
 */
class CoordinatesTerster final {
   public:
	void operator()();

   private:
	void testCoordinates();
	string incStr(string str);
};
}  // namespace cz::lastaapps::vimxel::table