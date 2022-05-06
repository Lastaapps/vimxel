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
using ST = shared_ptr<Term>;

class MultiOpNode : public OperatorNode {
    protected:
    vector<ST> mChildren;
    public:
    MultiOpNode(vector<Node*> children);
};

struct MultiOpNumNode : public MultiOpNode {
    MultiOpNumNode(vector<Node*> children);
};

struct MultiOpNumOrAreaNode : public MultiOpNode {
    MultiOpNumOrAreaNode(vector<Node*> children);
};

struct MultiOpNumOrTextNode : public MultiOpNode {
    MultiOpNumOrTextNode(vector<Node*> children);
};

struct MultiOpTextNode : public MultiOpNode {
    MultiOpTextNode(vector<Node*> children);
};
}

#endif