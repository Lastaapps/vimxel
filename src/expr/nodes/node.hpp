#ifndef H_NODE
#define H_NODE
#include <memory>

#include "terms.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using STerm = shared_ptr<Term>;

/**
 * @brief Nodes are members of evaluation tree.
 * Their method getValue() returns their value, that can be used
 * by other nodes in tree
 */
struct Node {
	virtual ~Node() = default;
	virtual STerm getValue() const = 0;
};
}  // namespace cz::lastaapps::vimxel::expr

#endif