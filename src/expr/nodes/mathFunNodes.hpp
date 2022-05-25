#ifndef H_MATH_FUN_NODE
#define H_MATH_FUN_NODE
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
 * @brief Pow operation according to cmath
 */
struct PowNode final : public BinOpNumNode {
	using BinOpNumNode::BinOpNumNode;
	string getName() const override;
	STerm getValue() const override;
};

/**
 * @brief Sqrt operation according to cmath
 */
struct SqrtNode final : public UnOpNumNode {
	using UnOpNumNode::UnOpNumNode;
	string getName() const override;
	STerm getValue() const override;
};

/**
 * @brief abs operation according to cmath
 */
struct AbsNode final : public UnOpNumNode {
	using UnOpNumNode::UnOpNumNode;
	string getName() const override;
	STerm getValue() const override;
};

/**
 * @brief modulo operation according to cmath
 */
struct ModuloNode final : public BinOpNumNode {
	using BinOpNumNode::BinOpNumNode;
	STerm getValue() const override;
	string getName() const override;
};

/**
 * @brief exp operation according to cmath
 */
struct ExponentialNode final : public UnOpNumNode {
	using UnOpNumNode::UnOpNumNode;
	string getName() const override;
	STerm getValue() const override;
};

/**
 * @brief ln operation according to cmath
 */
struct LnNode final : public UnOpNumNode {
	using UnOpNumNode::UnOpNumNode;
	string getName() const override;
	STerm getValue() const override;
};

/**
 * @brief log2 operation according to cmath
 */
struct Log2Node final : public UnOpNumNode {
	using UnOpNumNode::UnOpNumNode;
	string getName() const override;
	STerm getValue() const override;
};

/**
 * @brief log10 operation according to cmath
 */
struct Log10Node final : public UnOpNumNode {
	using UnOpNumNode::UnOpNumNode;
	string getName() const override;
	STerm getValue() const override;
};

/**
 * @brief log operation, ln(a)/ln(b) according to cmath
 */
struct LogNode final : public BinOpNumNode {
	using BinOpNumNode::BinOpNumNode;
	string getName() const override;
	STerm getValue() const override;
};
}  // namespace cz::lastaapps::vimxel::expr

#endif