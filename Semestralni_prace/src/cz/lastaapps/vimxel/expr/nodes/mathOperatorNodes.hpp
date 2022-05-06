#ifndef H_BIM_MATH_OP_NODE
#define H_BIM_MATH_OP_NODE
#include <memory>
#include "node.hpp"
#include "terms.hpp"
#include "unOperatorNodes.hpp"
#include "binOperatorNodes.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using ST = shared_ptr<Term>;

struct BinPlusNode : public BinOpNumNode {
    using BinOpNumNode::BinOpNumNode;
    ST getValue() override;
    string getName() const override;
};
struct BinMinusNode : public BinOpNumNode {
    using BinOpNumNode::BinOpNumNode;
    ST getValue() override;
    string getName() const override;
};
struct BinTimesNode : public BinOpNumNode {
    using BinOpNumNode::BinOpNumNode;
    ST getValue() override;
    string getName() const override;
};
struct BinDivideNode : public BinOpNumNode {
    using BinOpNumNode::BinOpNumNode;
    ST getValue() override;
    string getName() const override;
};

struct UnPlusNode : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    ST getValue() override;
    string getName() const override;
};
struct UnMinusNode : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    ST getValue() override;
    string getName() const override;
};
}

#endif