#ifndef H_GONIOMETRY_NODE
#define H_GONIOMETRY_NODE
#include <memory>
#include "node.hpp"
#include "terms.hpp"
#include "binOperatorNodes.hpp"
#include "unOperatorNodes.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using ST = shared_ptr<Term>;

// sin
struct SinNode : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    ST getValue() override;
};
// cos
struct CosNode : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    ST getValue() override;
};
// tan
struct TanNode : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    ST getValue() override;
};
// cot
struct CotNode : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    ST getValue() override;
};
// arcsin
struct ArcsinNode : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    ST getValue() override;
};
// arccos
struct ArccosNode : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    ST getValue() override;
};
// arctan
struct ArctanNode : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    ST getValue() override;
};
// arccot
struct ArccotNode : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    ST getValue() override;
};
}

#endif