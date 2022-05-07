#ifndef H_UN_OP_NODE
#define H_UN_OP_NODE
#include <memory>
#include <string>
#include "node.hpp"
#include "operatorNode.hpp"
#include "terms.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using ST = shared_ptr<Term>;

class UnOpNode : public OperatorNode {
    protected:
    const ST mChild;
    public:
    UnOpNode(Node * child);
};

struct UnOpNumNode : public UnOpNode {
    using UnOpNode::UnOpNode;
    shared_ptr<DoubleTerm> casted() const;
};

struct UnOpTextNode : public UnOpNode {
    using UnOpNode::UnOpNode;
    shared_ptr<TextTerm> casted() const;
};
}

#endif