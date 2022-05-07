#ifndef H_TERM_NODE
#define H_TERM_NODE
#include <memory>
#include "node.hpp"
#include "terms.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using ST = shared_ptr<Term>;
class TermNode final : Node {
    const ST mTerm;
    public:
    TermNode(ST term);
    ST getValue() const override;
};
}  // namespace cz::lastaapps::vimxel::expr

#endif