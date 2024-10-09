#include "Node.h"

using namespace std;

int Node::getBalanceFactor() const {
    int leftHeight = (left != nullptr) ? left->height() : -1;
    int rightHeight = (right != nullptr) ? right->height() : -1;
    return leftHeight - rightHeight;
}

int Node::height() const {
    return max(leftSubTreeHeight(), rightSubTreeHeight()) + 1;
}

int Node::leftSubTreeHeight() const {
    return (left != nullptr) ? left->height() : -1;
}

int Node::rightSubTreeHeight() const {
    return (right != nullptr) ? right->height() : -1;
}
