#include "termNode.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {

TermNode::TermNode(STerm term)
    : mTerm(term) {}
STerm TermNode::getValue() const {
    return mTerm;
}
}  // namespace cz::lastaapps::vimxel::expr