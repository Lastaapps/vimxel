#ifndef H_BIM_OP_NODE
#define H_BIM_OP_NODE
#include <memory>
#include <string>
#include "node.hpp"
#include "operatorNode.hpp"
#include "terms.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using STerm = shared_ptr<Term>;
using SNode = shared_ptr<Node>;

class BinOpNode : public OperatorNode {
    protected:
    const SNode mLeft, mRight;
    public:
    BinOpNode(SNode left, SNode right);
    BinOpNode(const vector<SNode>& args);
};

struct BinOpNumNode : public BinOpNode {
    using BinOpNode::BinOpNode;
    shared_ptr<DoubleTerm> castedLeft() const;
    shared_ptr<DoubleTerm> castedRight() const;
};

struct BinOpTextNode : public BinOpNode {
    using BinOpNode::BinOpNode;
    shared_ptr<TextTerm> castedLeft() const;
    shared_ptr<TextTerm> castedRight() const;
};
}

#endif