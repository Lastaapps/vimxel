#ifndef H_AGREGATE_NODE
#define H_AGREGATE_NODE
#include <memory>
#include "node.hpp"
#include "terms.hpp"
#include "multiOperatorNodes.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using ST = shared_ptr<Term>;

// sum
struct SumNode : public MultiOpNumOrAreaNode {
    using MultiOpNumOrAreaNode::MultiOpNumOrAreaNode;
    string getName() const override;
    ST getValue() override;
};
// max
struct MaxNode : public MultiOpNumOrAreaNode {
    using MultiOpNumOrAreaNode::MultiOpNumOrAreaNode;
    string getName() const override;
    ST getValue() override;
};
// min
struct MinNode : public MultiOpNumOrAreaNode {
    using MultiOpNumOrAreaNode::MultiOpNumOrAreaNode;
    string getName() const override;
    ST getValue() override;
};
// avg
struct AvgNode : public MultiOpNumOrAreaNode {
    using MultiOpNumOrAreaNode::MultiOpNumOrAreaNode;
    string getName() const override;
    ST getValue() override;
};
}

#endif