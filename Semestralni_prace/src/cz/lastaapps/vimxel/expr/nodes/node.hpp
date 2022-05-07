#ifndef H_NODE
#define H_NODE
#include <memory>
#include "terms.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using ST = shared_ptr<Term>;
struct Node {
    virtual ~Node() = default;
    virtual ST getValue() const = 0;
};
}  // namespace cz::lastaapps::vimxel::expr

#endif