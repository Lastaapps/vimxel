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
struct PowNode final : public BinOpNumNode {
    using BinOpNumNode::BinOpNumNode;
    string getName() const override;
    ST getValue() const override;
};
// sqrt
struct SqrtNode final : public BinOpNumNode {
    using BinOpNumNode::BinOpNumNode;
    string getName() const override;
    ST getValue() const override;
};
// abs
struct AbsNode final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    ST getValue() const override;
};
// e
struct ENode final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    ST getValue() const override;
};
// ln
struct LnNode final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    ST getValue() const override;
};
// log2
struct Log2Node final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    ST getValue() const override;
};
// log10
struct Log10Node final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    ST getValue() const override;
};
}

#endif