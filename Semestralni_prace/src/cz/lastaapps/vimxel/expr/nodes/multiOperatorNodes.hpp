#ifndef H_MULTI_OP_NODE
#define H_MULTI_OP_NODE
#include <memory>
#include <string>
#include <vector>

#include "node.hpp"
#include "operatorNode.hpp"
#include "terms.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using STerm = shared_ptr<Term>;
using SNode = shared_ptr<Node>;

/**
 * @brief Parent of all the operators with 1 or more arguments
 */
class MultiOpNode : public OperatorNode {
   public:
	MultiOpNode(const vector<SNode>& children);

   protected:
	const vector<SNode> mChildren;
	vector<STerm> mapped() const;
};

/**
 * @brief Provides casted values to double to it's children
 */
struct MultiOpNumNode : public MultiOpNode {
	using MultiOpNode::MultiOpNode;

   protected:
	vector<shared_ptr<DoubleTerm>> casted() const;
};

/**
 * @brief Provides checked values od double or area to it's children
 */
struct MultiOpNumOrAreaNode : public MultiOpNode {
	using MultiOpNode::MultiOpNode;

   protected:
	vector<STerm> checked() const;
};

/**
 * @brief Provides checked values of number or text to it's children
 */
struct MultiOpNumOrTextNode : public MultiOpNode {
	using MultiOpNode::MultiOpNode;

   protected:
	vector<STerm> checked() const;
};

/**
 * @brief Provides casted values to string to it's children
 */
struct MultiOpTextNode : public MultiOpNode {
	using MultiOpNode::MultiOpNode;

   protected:
	vector<shared_ptr<TextTerm>> casted() const;
};
}  // namespace cz::lastaapps::vimxel::expr

#endif