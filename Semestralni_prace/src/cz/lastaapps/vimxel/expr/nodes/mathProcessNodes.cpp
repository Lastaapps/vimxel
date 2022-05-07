#include "mathProcessNodes.hpp"
#include <cmath>


using namespace std;
namespace cz::lastaapps::vimxel::expr {

// round
string RoundNode::getName() const { return "round"; }
ST RoundNode::getValue() const {
    return make_shared<DoubleTerm>(
        llroundl(casted() -> getValue())
    );
}

// ceil
string CeilNode::getName() const { return "ceil"; }
ST CeilNode::getValue() const {
    return make_shared<DoubleTerm>(
        ceill(casted() -> getValue())
    );
}

// floor
string FloorNode::getName() const { return "floor"; }
ST FloorNode::getValue() const {
    return make_shared<DoubleTerm>(
        floorl(casted() -> getValue())
    );
}

// trunc
string TruncNode::getName() const { return "trunc"; }
ST TruncNode::getValue() const {
    return make_shared<DoubleTerm>(
        truncl(casted() -> getValue())
    );
}
}  