#ifndef H_MATH_PROCESS_NODE
#define H_MATH_PROCESS_NODE
#include <memory>

#include "binOperatorNodes.hpp"
#include "node.hpp"
#include "terms.hpp"
#include "unOperatorNodes.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using STerm = shared_ptr<Term>;
using SNode = shared_ptr<Node>;

/**
 * @brief Round number given according to cmath lib
 */
struct RoundNode final : public UnOpNumNode {
	using UnOpNumNode::UnOpNumNode;
	string getName() const override;
	STerm getValue() const override;
};

/**
 * @brief Ceil number given according to cmath lib
 */
struct CeilNode final : public UnOpNumNode {
	using UnOpNumNode::UnOpNumNode;
	string getName() const override;
	STerm getValue() const override;
};

/**
 * @brief Floor number given according to cmath lib
 */
struct FloorNode final : public UnOpNumNode {
	using UnOpNumNode::UnOpNumNode;
	string getName() const override;
	STerm getValue() const override;
};

/**
 * @brief Trunc number given according to cmath lib
 */
struct TruncNode final : public UnOpNumNode {
	using UnOpNumNode::UnOpNumNode;
	string getName() const override;
	STerm getValue() const override;
};
}  // namespace cz::lastaapps::vimxel::expr

#endif