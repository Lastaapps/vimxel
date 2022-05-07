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
struct SumNode final : public MultiOpNumOrAreaNode {
    using MultiOpNumOrAreaNode::MultiOpNumOrAreaNode;
    string getName() const override;
    ST getValue() const override;
    private:
    void addTerm(ST term, long double& sum) const;
};
// max
struct MaxNode final : public MultiOpNumOrAreaNode {
    using MultiOpNumOrAreaNode::MultiOpNumOrAreaNode;
    string getName() const override;
    ST getValue() const override;
};
// min
struct MinNode final : public MultiOpNumOrAreaNode {
    using MultiOpNumOrAreaNode::MultiOpNumOrAreaNode;
    string getName() const override;
    ST getValue() const override;
};
// avg
struct AvgNode final : public MultiOpNumOrAreaNode {
    using MultiOpNumOrAreaNode::MultiOpNumOrAreaNode;
    string getName() const override;
    ST getValue() const override;
};
}

#endif