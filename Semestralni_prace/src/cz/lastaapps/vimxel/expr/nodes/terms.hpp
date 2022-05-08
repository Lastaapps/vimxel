#ifndef H_TERM
#define H_TERM
#include <memory>
#include <string>
#include <vector>

using namespace std;
namespace cz::lastaapps::vimxel::expr {

struct Term {
	virtual ~Term() = default;
	virtual string toString() const = 0;
};
struct SingleTerm : public Term {};

class DoubleTerm final : public SingleTerm {
	const long double mValue;

   public:
	explicit DoubleTerm(long double value);
	long double getValue() const;
	string toString() const override;
};

class TextTerm final : public SingleTerm {
	const string mValue;

   public:
	explicit TextTerm(const string& value);
	const string& getValue() const;
	string toString() const override;
};

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