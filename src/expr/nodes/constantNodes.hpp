#ifndef H_CONSTANT_NODES
#define H_CONSTANT_NODES
#include <memory>

#include "node.hpp"
#include "terms.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using STerm = shared_ptr<Term>;
using SNode = shared_ptr<Node>;

/**
 * @brief Pi constant node
 */
struct PiNode final : public Node {
	STerm getValue() const override;
};

/**
 * @brief Euler constant node
 */
struct EulersNumberNode final : public Node {
	STerm getValue() const override;
};

/**
 * @brief Lightspeed constant node
 */
struct LightSpeedNode final : public Node {
	STerm getValue() const override;
};

/**
 * @brief Golden ration constant node
 */
struct GoldenRationNode final : public Node {
	STerm getValue() const override;
};
}  // namespace cz::lastaapps::vimxel::expr

#endif