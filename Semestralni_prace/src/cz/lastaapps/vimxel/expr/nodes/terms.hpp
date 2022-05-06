#ifndef H_TERM
#define H_TERM
#include <memory>
#include <string>
#include <vector>

using namespace std;
namespace cz::lastaapps::vimxel::expr {

struct Term {
    virtual ~Term() = default;
};

class DoubleTerm : public Term {
    long double mValue;
    public:
    DoubleTerm(long double value);
    long double getValue() const;
};

class TextTerm : public Term {
    string mValue;
    public:
    TextTerm(const string& value);
    const string& getValue() const;
};

class AreaTerm : public Term {
    vector<shared_ptr<Term>> mValue;
    public:
	 AreaTerm(const string& value);
	 const vector<shared_ptr<Term>>& getValue() const;
};
}

#endif