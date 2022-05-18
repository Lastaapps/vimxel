#ifndef H_TEXT_MANIP_NODE
#define H_TEXT_MANIP_NODE
#include <memory>

#include "multiOperatorNodes.hpp"
#include "node.hpp"
#include "terms.hpp"
#include "unOperatorNodes.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using STerm = shared_ptr<Term>;
using SNode = shared_ptr<Node>;

/**
 * @brief Concats more strings or number together
 */
struct ConcatNode final : public MultiOpNumOrTextNode {
	using MultiOpNumOrTextNode::MultiOpNumOrTextNode;
	string getName() const override;
	STerm getValue() const override;
};

/**
 * @brief Converts string to lowercase
 */
struct LowerNode final : public UnOpTextNode {
	using UnOpTextNode::UnOpTextNode;
	string getName() const override;
	STerm getValue() const override;
};

/**
 * @brief Converts string to uppercase
 */
struct UpperNode final : public UnOpTextNode {
	using UnOpTextNode::UnOpTextNode;
	string getName() const override;
	STerm getValue() const override;
};

}  // namespace cz::lastaapps::vimxel::expr

#endif