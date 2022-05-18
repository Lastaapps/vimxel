#ifndef H_AGGREGATE_NODE
#define H_AGGREGATE_NODE
#include <memory>

#include "multiOperatorNodes.hpp"
#include "node.hpp"
#include "terms.hpp"

using namespace std;
namespace cz::lastaapps::vimxel::expr {
using STerm = shared_ptr<Term>;
using SNode = shared_ptr<Node>;

/**
 * @brief Sums passed args
 */
struct SumNode final : public MultiOpNumOrAreaNode {
	using MultiOpNumOrAreaNode::MultiOpNumOrAreaNode;
	string getName() const override;
	STerm getValue() const override;

   private:
	void addTerm(STerm term, long double& sum) const;
};
/**
 * @brief Find max in args given
 */
struct MaxNode final : public MultiOpNumOrAreaNode {
	using MultiOpNumOrAreaNode::MultiOpNumOrAreaNode;
	string getName() const override;
	STerm getValue() const override;

   private:
	long double getFirst(STerm term) const;
	void checkTerm(STerm term, long double& max) const;
};
/**
 * @brief Find min in args given
 */
struct MinNode final : public MultiOpNumOrAreaNode {
	using MultiOpNumOrAreaNode::MultiOpNumOrAreaNode;
	string getName() const override;
	STerm getValue() const override;

   private:
	long double getFirst(STerm term) const;
	void checkTerm(STerm term, long double& min) const;
};
/**
 * @brief Find average in args given
 */
struct AvgNode final : public MultiOpNumOrAreaNode {
	using MultiOpNumOrAreaNode::MultiOpNumOrAreaNode;
	string getName() const override;
	STerm getValue() const override;

   private:
	void addTerm(STerm term, long double& sum, size_t& total) const;
};
}  // namespace cz::lastaapps::vimxel::expr

#endif