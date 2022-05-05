


class Term {};
class Number : Term {};
class Text : Term {};

class Operator {};

class Node {
    Term& getValue();
};
class BinaryOperator : Node {
    BinaryOperator(Node, Node);
};
class PlusOperator : BinaryOperator {
    using BinaryOperator::BinaryOperator;
    Term& getValue(); // a + b
};


