#ifndef H_AGREGATE_NODE
#define H_AGREGATE_NODE
#include <memory>
#include "node.hpp"
#include "terms.hpp"
#include "unOperatorNodes.hpp"
#include "multiOperatorNodes.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using ST = shared_ptr<Term>;

// concat
struct ConcatNode final : public MultiOpNumOrTextNode {
    using MultiOpNumOrTextNode::MultiOpNumOrTextNode;
    string getName() const override;
    ST getValue() const override;
};

// lower
struct LowerNode final : public UnOpTextNode {
    using UnOpTextNode::UnOpTextNode;
    string getName() const override;
    ST getValue() const override;
};

// upper
struct UpperNode final : public UnOpTextNode {
    using UnOpTextNode::UnOpTextNode;
    string getName() const override;
    ST getValue() const override;
};

}

#endif