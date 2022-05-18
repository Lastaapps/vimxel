#ifndef H_OPERATOR_NODE
#define H_OPERATOR_NODE
#include <memory>

#include "node.hpp"
#include "terms.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {

/**
 * @brief This node is parrent of all operators and functions
 * brings operator getName() method used for error reporting
 */
struct OperatorNode : public Node {
   protected:
	virtual string getName() const { return "unknown"; };
};
}  // namespace cz::lastaapps::vimxel::expr

#endif