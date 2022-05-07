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
using SN = shared_ptr<Node>;

class MultiOpNode : public OperatorNode {
    protected:
    const vector<ST> mChildren;
    public:
    MultiOpNode(const vector<SN>& children);
    private:
    static vector<ST> map(const vector<SN>& src);
};

struct MultiOpNumNode : public MultiOpNode {
    MultiOpNumNode(const vector<SN>& children);
};

struct MultiOpNumOrAreaNode : public MultiOpNode {
    MultiOpNumOrAreaNode(const vector<SN>& children);
};

struct MultiOpNumOrTextNode : public MultiOpNode {
    MultiOpNumOrTextNode(const vector<SN>& children);
};

struct MultiOpTextNode : public MultiOpNode {
    MultiOpTextNode(const vector<SN>& children);
};
}

#endif