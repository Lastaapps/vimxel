#ifndef H_TRIGONOMETRY_NODE
#define H_TRIGONOMETRY_NODE
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
 * @brief Sin according to cmath library
 */
struct SinNode final : public UnOpNumNode {
	using UnOpNumNode::UnOpNumNode;
	string getName() const override;
	STerm getValue() const override;
};

/**
 * @brief Cos according to cmath library
 */
struct CosNode final : public UnOpNumNode {
	using UnOpNumNode::UnOpNumNode;
	string getName() const override;
	STerm getValue() const override;
};

/**
 * @brief Tan according to cmath library
 */
struct TanNode final : public UnOpNumNode {
	using UnOpNumNode::UnOpNumNode;
	string getName() const override;
	STerm getValue() const override;
};

/**
 * @brief Cot according to cmath library
 */
struct CotNode final : public UnOpNumNode {
	using UnOpNumNode::UnOpNumNode;
	string getName() const override;
	STerm getValue() const override;
};

/**
 * @brief arcsin according to cmath library
 */
struct ArcsinNode final : public UnOpNumNode {
	using UnOpNumNode::UnOpNumNode;
	string getName() const override;
	STerm getValue() const override;
};

/**
 * @brief arccos according to cmath library
 */
struct ArccosNode final : public UnOpNumNode {
	using UnOpNumNode::UnOpNumNode;
	string getName() const override;
	STerm getValue() const override;
};

/**
 * @brief arctan according to cmath library
 */
struct ArctanNode final : public UnOpNumNode {
	using UnOpNumNode::UnOpNumNode;
	string getName() const override;
	STerm getValue() const override;
};

/**
 * @brief arccot according to cmath library
 */
struct ArccotNode final : public UnOpNumNode {
	using UnOpNumNode::UnOpNumNode;
	string getName() const override;
	STerm getValue() const override;
};
}  // namespace cz::lastaapps::vimxel::expr

#endif