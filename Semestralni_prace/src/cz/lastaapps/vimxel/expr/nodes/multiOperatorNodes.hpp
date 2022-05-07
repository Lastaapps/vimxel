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
    const vector<ST> mChildren;
    public:
    MultiOpNode(vector<ST> children);
};

struct MultiOpNumNode : public MultiOpNode {
    MultiOpNumNode(vector<ST> children);
};

struct MultiOpNumOrAreaNode : public MultiOpNode {
    MultiOpNumOrAreaNode(vector<ST> children);
};

struct MultiOpNumOrTextNode : public MultiOpNode {
    MultiOpNumOrTextNode(vector<ST> children);
};

struct MultiOpTextNode : public MultiOpNode {
    MultiOpTextNode(vector<ST> children);
};
}

#endif