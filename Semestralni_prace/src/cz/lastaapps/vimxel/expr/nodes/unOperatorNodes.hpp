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
    ST mChild;
    public:
    UnOpNode(Node * child);
};

struct UnOpNumNode : public UnOpNode {
    UnOpNumNode(Node * child);
};

struct UnOpTextNode : public UnOpNode {
    UnOpTextNode(Node * child);
};
}

#endif