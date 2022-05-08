#ifndef H_MULTI_OP_NODE
#define H_MULTI_OP_NODE
#include <memory>
#include <vector>
#include <string>
#include "node.hpp"
#include "operatorNode.hpp"
#include "terms.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using STerm = shared_ptr<Term>;
using SNode = shared_ptr<Node>;

class MultiOpNode : public OperatorNode {
    public:
    MultiOpNode(const vector<SNode>& children);
    protected:
    const vector<SNode> mChildren;
    vector<STerm> mapped() const;
};

struct MultiOpNumNode : public MultiOpNode {
    using MultiOpNode::MultiOpNode;
    protected:
    vector<shared_ptr<DoubleTerm>> casted() const;
};

struct MultiOpNumOrAreaNode : public MultiOpNode {
    using MultiOpNode::MultiOpNode;
    protected:
    vector<STerm> checked() const;
};

struct MultiOpNumOrTextNode : public MultiOpNode {
    using MultiOpNode::MultiOpNode;
    protected:
    vector<STerm> checked() const;
};

struct MultiOpTextNode : public MultiOpNode {
    using MultiOpNode::MultiOpNode;
    protected:
    vector<shared_ptr<TextTerm>> casted() const;
};
}

#endif