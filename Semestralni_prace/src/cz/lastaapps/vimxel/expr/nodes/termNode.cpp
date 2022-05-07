#include "termNode.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {

TermNode::TermNode(ST term)
    : mTerm(term) {}
ST TermNode::getValue() const {
    return mTerm;
}
}  // namespace cz::lastaapps::vimxel::expr