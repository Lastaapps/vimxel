#ifndef H_OPERATOR_NODE
#define H_OPERATOR_NODE
#include <memory>
#include "terms.hpp"
#include "node.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
struct OperatorNode : Node {
    protected:
    virtual string getName() const { return "unknown"; };
};
}  // namespace cz::lastaapps::vimxel::expr

#endif