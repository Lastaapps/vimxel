#ifndef H_MATH_FUN_NODE
#define H_MATH_FUN_NODE
#include <memory>
#include "node.hpp"
#include "terms.hpp"
#include "binOperatorNodes.hpp"
#include "unOperatorNodes.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using STerm = shared_ptr<Term>;
using SNode = shared_ptr<Node>;

// pow
struct PowNode final : public BinOpNumNode {
    using BinOpNumNode::BinOpNumNode;
    string getName() const override;
    STerm getValue() const override;
};
// sqrt
struct SqrtNode final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    STerm getValue() const override;
};
// abs
struct AbsNode final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    STerm getValue() const override;
};
struct ModuloNode final : public BinOpNumNode {
    using BinOpNumNode::BinOpNumNode;
    STerm getValue() const override;
    string getName() const override;
};
// exp
struct ExponentialNode final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    STerm getValue() const override;
};
// ln
struct LnNode final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    STerm getValue() const override;
};
// log2
struct Log2Node final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    STerm getValue() const override;
};
// log10
struct Log10Node final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    STerm getValue() const override;
};
// log
struct LogNode final : public BinOpNumNode {
    using BinOpNumNode::BinOpNumNode;
    string getName() const override;
    STerm getValue() const override;
};
}

#endif