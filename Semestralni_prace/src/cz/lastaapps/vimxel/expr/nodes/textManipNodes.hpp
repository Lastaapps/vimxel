#ifndef H_AGREGATE_NODE
#define H_AGREGATE_NODE
#include <memory>
#include "node.hpp"
#include "terms.hpp"
#include "unOperatorNodes.hpp"
#include "multiOperatorNodes.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using STerm = shared_ptr<Term>;
using SNode = shared_ptr<Node>;

// concat
struct ConcatNode final : public MultiOpNumOrTextNode {
    using MultiOpNumOrTextNode::MultiOpNumOrTextNode;
    string getName() const override;
    STerm getValue() const override;
};

// lower
struct LowerNode final : public UnOpTextNode {
    using UnOpTextNode::UnOpTextNode;
    string getName() const override;
    STerm getValue() const override;
};

// upper
struct UpperNode final : public UnOpTextNode {
    using UnOpTextNode::UnOpTextNode;
    string getName() const override;
    STerm getValue() const override;
};

}

#endif