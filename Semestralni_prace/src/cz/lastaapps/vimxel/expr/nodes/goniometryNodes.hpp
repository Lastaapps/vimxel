#ifndef H_GONIOMETRY_NODE
#define H_GONIOMETRY_NODE
#include <memory>
#include "node.hpp"
#include "terms.hpp"
#include "binOperatorNodes.hpp"
#include "unOperatorNodes.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using STerm = shared_ptr<Term>;
using SNode = shared_ptr<Node>;

// sin
struct SinNode final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    STerm getValue() const override;
};
// cos
struct CosNode final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    STerm getValue() const override;
};
// tan
struct TanNode final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    STerm getValue() const override;
};
// cot
struct CotNode final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    STerm getValue() const override;
};
// arcsin
struct ArcsinNode final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    STerm getValue() const override;
};
// arccos
struct ArccosNode final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    STerm getValue() const override;
};
// arctan
struct ArctanNode final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    STerm getValue() const override;
};
// arccot
struct ArccotNode final : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    STerm getValue() const override;
};
}

#endif