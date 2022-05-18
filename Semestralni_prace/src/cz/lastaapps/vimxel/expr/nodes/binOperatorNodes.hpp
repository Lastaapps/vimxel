#ifndef H_BIM_OP_NODE
#define H_BIM_OP_NODE
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
 * @brief Parent of binary operators and funcions
 */
class BinOpNode : public OperatorNode {
   protected:
	const SNode mLeft, mRight;

   public:
	/**
	 * @brief Construct a new Bin Op Node object
	 *
	 * @param left left operand
	 * @param right right operand
	 */
	BinOpNode(SNode left, SNode right);
	/**
	 * @brief Construct a new Bin Op Node object
	 *
	 * @param args left and right operands in this order
	 * @throw ivalid_argument if there are 0 or 3 =< args
	 */
	BinOpNode(const vector<SNode>& args);
};

/**
 * @brief Provides checked number values to it's children
 */
struct BinOpNumNode : public BinOpNode {
	using BinOpNode::BinOpNode;
	shared_ptr<DoubleTerm> castedLeft() const;
	shared_ptr<DoubleTerm> castedRight() const;
};

/**
 * @brief Provides checked text values to it's children
 */
struct BinOpTextNode : public BinOpNode {
	using BinOpNode::BinOpNode;
	shared_ptr<TextTerm> castedLeft() const;
	shared_ptr<TextTerm> castedRight() const;
};
}  // namespace cz::lastaapps::vimxel::expr

#endif