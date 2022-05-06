#ifndef H_BIM_OP_NODE
#define H_BIM_OP_NODE
#include <memory>
#include <string>
#include "node.hpp"
#include "operatorNode.hpp"
#include "terms.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using ST = shared_ptr<Term>;

class BinOpNode : public OperatorNode {
    protected:
    ST mLeft, mRight;
    public:
    BinOpNode(Node * left, Node * right);
};

struct BinOpNumNode : public BinOpNode {
    BinOpNumNode(Node * left, Node * right);
};

struct BinOpTextNode : public BinOpNode {
    BinOpTextNode(Node * left, Node * right);
};
}

#endif