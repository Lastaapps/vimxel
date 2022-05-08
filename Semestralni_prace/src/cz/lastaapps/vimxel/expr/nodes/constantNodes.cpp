#include "constantNodes.hpp"
#include <math.h>

using namespace std;
namespace cz::lastaapps::vimxel::expr {

STerm PiNode::getValue() const {
    return make_shared<DoubleTerm>(M_PI);
}
STerm EulersNumberNode::getValue() const {
    return make_shared<DoubleTerm>(M_E);
}
STerm LightSpeedNode::getValue() const {
    return make_shared<DoubleTerm>(299792458);
}
STerm GoldenRationNode::getValue() const {
    return make_shared<DoubleTerm>(1.6180339887498948482045868343656381177203091798057628621L);
}

}  // namespace cz::lastaapps::vimxel::expr