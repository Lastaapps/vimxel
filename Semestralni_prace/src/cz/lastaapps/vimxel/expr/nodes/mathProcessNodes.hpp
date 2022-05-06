#ifndef H_MATH_PROCESS_NODE
#define H_MATH_PROCESS_NODE
#include <memory>
#include "node.hpp"
#include "terms.hpp"
#include "binOperatorNodes.hpp"
#include "unOperatorNodes.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using ST = shared_ptr<Term>;

// round
struct RoundNode : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    ST getValue() override;
};
// ceil
struct CeilNode : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    ST getValue() override;
};
// floor
struct FloorNode : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    ST getValue() override;
};
// tail
struct TailNode : public UnOpNumNode {
    using UnOpNumNode::UnOpNumNode;
    string getName() const override;
    ST getValue() override;
};
}

#endif