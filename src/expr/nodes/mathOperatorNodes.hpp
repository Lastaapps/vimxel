#ifndef H_BIM_MATH_OP_NODE
#define H_BIM_MATH_OP_NODE
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
 * @brief Norman binary plus operator
 */
struct BinPlusNode final : public BinOpNumNode {
	using BinOpNumNode::BinOpNumNode;
	STerm getValue() const override;
	string getName() const override;
};

/**
 * @brief Norman binary minus operator
 */
struct BinMinusNode final : public BinOpNumNode {
	using BinOpNumNode::BinOpNumNode;
	STerm getValue() const override;
	string getName() const override;
};

/**
 * @brief Norman times operator
 */
struct TimesNode final : public BinOpNumNode {
	using BinOpNumNode::BinOpNumNode;
	STerm getValue() const override;
	string getName() const override;
};

/**
 * @brief Norman divide operator
 */
struct DivideNode final : public BinOpNumNode {
	using BinOpNumNode::BinOpNumNode;
	STerm getValue() const override;
	string getName() const override;
};

/**
 * @brief Normal unary plus, in fact no operation
 */
struct UnPlusNode final : public UnOpNumNode {
	using UnOpNumNode::UnOpNumNode;
	STerm getValue() const override;
	string getName() const override;
};

/**
 * @brief Normal unary minus
 */
struct UnMinusNode final : public UnOpNumNode {
	using UnOpNumNode::UnOpNumNode;
	STerm getValue() const override;
	string getName() const override;
};
}  // namespace cz::lastaapps::vimxel::expr

#endif