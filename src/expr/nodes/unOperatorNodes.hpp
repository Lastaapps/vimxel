#ifndef H_UN_OP_NODE
#define H_UN_OP_NODE
#include <memory>
#include <string>

#include "node.hpp"
#include "operatorNode.hpp"
#include "terms.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using STerm = shared_ptr<Term>;
using SNode = shared_ptr<Node>;

/**
 * @brief Unary operator parrent
 */
class UnOpNode : public OperatorNode {
   protected:
	const SNode mChild;

   public:
	/**
	 * @brief Construct a new Un Op Node object
	 *
	 * @param child child node
	 */
	UnOpNode(SNode child);
	/**
	 * @brief Construct a new Un Op Node object
	 *
	 * @param child child node
	 * @throw invalid_argument if there are 0 or 2 <= nodes in the list
	 */
	UnOpNode(const vector<SNode>& args);
};

/**
 * @brief Group of unary nodes with number only input
 */
struct UnOpNumNode : public UnOpNode {
	using UnOpNode::UnOpNode;
	/**
	 * @brief Check and cast term from node
	 *
	 * @return casted term
	 */
	shared_ptr<DoubleTerm> casted() const;
};

/**
 * @brief Group of unary nodes with text only input
 */
struct UnOpTextNode : public UnOpNode {
	using UnOpNode::UnOpNode;
	/**
	 * @brief Check and cast term from node
	 *
	 * @return casted term
	 */
	shared_ptr<TextTerm> casted() const;
};
}  // namespace cz::lastaapps::vimxel::expr

#endif