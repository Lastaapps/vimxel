#ifndef H_BIM_MATH_OP_NODE
#define H_BIM_MATH_OP_NODE
#include <memory>
#include "node.hpp"
#include "terms.hpp"
#include "unOperatorNodes.hpp"
#include "binOperatorNodes.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using STerm = shared_ptr<Term>;
using SNode = shared_ptr<Node>;

struct BinPlusNode final : public BinOpNumNode {
    using BinOpNumNode::BinOpNumNode;
    STerm getValue() const override;
    string getName() const override;
};
struct BinMinusNode final : public BinOpNumNode {
    using BinOpNumNode::BinOpNumNode;
    STerm getValue() const override;
    string getName() const override;
};
struct BinTimesNode final : public BinOpNumNode {
    using BinOpNumNode::BinOpNumNode;
    STerm getValue() const override;
    string getName() const override;
};
struct BinDivideNode final : public BinOpNumNode {
    using BinOpNumNode::BinOpNumNode;
    STerm getValue() const override;
    string getName() const override;
};

struct UnPlusNode final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    STerm getValue() const override;
    string getName() const override;
};
struct UnMinusNode final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    STerm getValue() const override;
    string getName() const override;
};
}

#endif