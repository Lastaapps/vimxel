#ifndef H_CONSTATN_NODES
#define H_CONSTATN_NODES
#include <memory>
#include "node.hpp"
#include "terms.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using STerm = shared_ptr<Term>;
using SNode = shared_ptr<Node>;

struct PiNode final : public Node {
    STerm getValue() const override;
};
struct EulersNumberNode final : public Node {
    STerm getValue() const override;
};
struct LightSpeedNode final : public Node {
    STerm getValue() const override;
};
struct GoldenRationNode final : public Node {
    STerm getValue() const override;
};
}  // namespace cz::lastaapps::vimxel::expr

#endif