#ifndef H_TERM
#define H_TERM
#include <memory>
#include <string>
#include <vector>

using namespace std;
namespace cz::lastaapps::vimxel::expr {

/**
 * @brief Represents result of a calculation or cell value
 */
struct Term {
	virtual ~Term() = default;
	/**
	 * @brief Gets string representation of the term
	 * 
	 * @return string representation 
	 */
	virtual string toString() const = 0;
};
/**
 * @brief Group of terms with single value, opposite to area
 */
struct SingleTerm : public Term {};

/**
 * @brief Term holding double value
 */
class DoubleTerm final : public SingleTerm {
	const long double mValue;

   public:
	explicit DoubleTerm(long double value);
	long double getValue() const;
	string toString() const override;
};

/**
 * @brief Term holding text value
 */
class TextTerm final : public SingleTerm {
	const string mValue;

   public:
	explicit TextTerm(const string& value);
	const string& getValue() const;
	string toString() const override;
};

/**
 * @brief Term holding area - list of terms
 */
class AreaTerm final : public Term {
	using SSingleTerm = shared_ptr<SingleTerm>;
	const vector<SSingleTerm> mValue;

   public:
	explicit AreaTerm(const vector<SSingleTerm>& value);
	const vector<SSingleTerm>& getValue() const;
	string toString() const override;
};
}  // namespace cz::lastaapps::vimxel::expr

#endif