#ifndef H_MATH_PROCESS_NODE
#define H_MATH_PROCESS_NODE
#include <memory>
#include "node.hpp"
#include "terms.hpp"
#include "binOperatorNodes.hpp"
#include "unOperatorNodes.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using STerm = shared_ptr<Term>;
using SNode = shared_ptr<Node>;

// round
struct RoundNode final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    STerm getValue() const override;
};
// ceil
struct CeilNode final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    STerm getValue() const override;
};
// floor
struct FloorNode final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    STerm getValue() const override;
};
// trunc
struct TruncNode final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    STerm getValue() const override;
};
}

#endif