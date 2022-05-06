#ifndef H_MATH_FUN_NODE
#define H_MATH_FUN_NODE
#include <memory>
#include "node.hpp"
#include "terms.hpp"
#include "binOperatorNodes.hpp"
#include "unOperatorNodes.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using ST = shared_ptr<Term>;

// pow
struct PowNode : public BinOpNumNode {
    using BinOpNumNode::BinOpNumNode;
    string getName() const override;
    ST getValue() override;
};
// sqrt
struct SqrtNode : public BinOpNumNode {
    using BinOpNumNode::BinOpNumNode;
    string getName() const override;
    ST getValue() override;
};
// abs
struct AbsNode : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    ST getValue() override;
};
// e
struct ENode : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    ST getValue() override;
};
// ln
struct LnNode : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    ST getValue() override;
};
// log2
struct Log2Node : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    ST getValue() override;
};
// log10
struct Log10Node : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    ST getValue() override;
};
}

#endif