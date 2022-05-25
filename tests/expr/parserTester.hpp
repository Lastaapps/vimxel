#pragma once

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>

#include "../../src/expr/parser.hpp"
#include "../testUtils.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {

using SSingleTerm = shared_ptr<SingleTerm>;

/**
 * @brief Tests parser with various valid and invalid inputs, doesn't control correctness of calculations
 */
struct ParserTester final {
	void operator()();

   private:
	function<SSingleTerm(const table::Coordinates&)> provider = [](const table::Coordinates&) -> SSingleTerm { return make_shared<DoubleTerm>(0); };
	void testExprs();
};

}  // namespace cz::lastaapps::vimxel::expr