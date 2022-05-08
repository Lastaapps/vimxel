#ifndef H_AGREGATE_NODE
#define H_AGREGATE_NODE
#include <memory>
#include "node.hpp"
#include "terms.hpp"
#include "multiOperatorNodes.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using STerm = shared_ptr<Term>;
using SNode = shared_ptr<Node>;

// sum
struct SumNode final : public MultiOpNumOrAreaNode {
    using MultiOpNumOrAreaNode::MultiOpNumOrAreaNode;
    string getName() const override;
    STerm getValue() const override;
    private:
    void addTerm(STerm term, long double& sum) const;
};
// max
struct MaxNode final : public MultiOpNumOrAreaNode {
    using MultiOpNumOrAreaNode::MultiOpNumOrAreaNode;
    string getName() const override;
    STerm getValue() const override;
    private:
    long double getFirst(STerm term) const;
    void checkTerm(STerm term, long double& max) const;
};
// min
struct MinNode final : public MultiOpNumOrAreaNode {
    using MultiOpNumOrAreaNode::MultiOpNumOrAreaNode;
    string getName() const override;
    STerm getValue() const override;
    private:
    long double getFirst(STerm term) const;
    void checkTerm(STerm term, long double& min) const;
};
// avg
struct AvgNode final : public MultiOpNumOrAreaNode {
    using MultiOpNumOrAreaNode::MultiOpNumOrAreaNode;
    string getName() const override;
    STerm getValue() const override;
    private:
    void addTerm(STerm term, long double& sum, size_t& total) const;
};
}

#endif