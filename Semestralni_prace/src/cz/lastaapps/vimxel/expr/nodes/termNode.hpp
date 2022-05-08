#ifndef H_TERM_NODE
#define H_TERM_NODE
#include <memory>
#include "node.hpp"
#include "terms.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using STerm = shared_ptr<Term>;
using SNode = shared_ptr<Node>;

class TermNode final : public Node {
    const STerm mTerm;
    public:
    TermNode(STerm term);
    STerm getValue() const override;
};
}  // namespace cz::lastaapps::vimxel::expr

#endif