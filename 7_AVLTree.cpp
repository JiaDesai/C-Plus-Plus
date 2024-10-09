#include "AVLTree.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

AVLTree::~AVLTree() {
    recursiveDelete(root);
}

void AVLTree::insert(const string &newString) {
    if (!root) root = new Node(newString, nullptr);
    else {
        Node *currNode = root;
        while (currNode) {
            if (newString < currNode->value) {
                if (!currNode->left) currNode->left = new Node(newString, currNode);
                else currNode = currNode->left;
            } else if (currNode->value < newString) {
                if (!currNode->right) currNode->right = new Node(newString, currNode);
                else currNode = currNode->right;
            } else return;
        }
        Node *node = findUnbalancedNode(currNode);
        if (node) rotate(node);
    }
}

int AVLTree::balanceFactor(Node *node) const {
    if (!node) throw runtime_error("AVLTree::balanceFactor() cannot be called on a nullptr!!!");
    return node->getBalanceFactor();
}

void AVLTree::printBalanceFactors() const {
    printBalanceFactors(root);
    cout << endl;
}

void AVLTree::printBalanceFactors(Node *node) const {
    if (!node) return;
    printBalanceFactors(node->left);
    cout << node->value << '(' << node->getBalanceFactor() << "), ";
    printBalanceFactors(node->right);
}

Node *AVLTree::findUnbalancedNode(Node *node) const {
    if (!node) return nullptr;
    if (abs(node->getBalanceFactor()) > 1) return node;
    return findUnbalancedNode(node->parent);
}

void AVLTree::rotate(Node *node) {
    int factor = node->getBalanceFactor();
    if (factor < -1) {
        if (node->right->getBalanceFactor() > 0) rotateRight(node->right);
        rotateLeft(node);
    } else if (factor > 1) {
        if (node->left->getBalanceFactor() < 0) rotateLeft(node->left);
        rotateRight(node);
    }
}

void AVLTree::rotateLeft(Node *node) {
    Node *parent = node->parent, *nodeF = node->right, *nodeD = node, *nodeE = nodeF->left;
    nodeD->right = nodeE;
    nodeF->left = nodeD;
    updateParent(node, parent, nodeF);
}

void AVLTree::rotateRight(Node *node) {
    Node *parent = node->parent, *nodeB = node->left, *nodeD = node, *nodeC = nodeB->right;
    nodeB->right = nodeD;
    nodeD->left = nodeC;
    updateParent(node, parent, nodeB);
}

void AVLTree::recursiveDelete(Node *node) {
    if (!node) return;
    recursiveDelete(node->left);
    recursiveDelete(node->right);
    delete node;
}

void AVLTree::updateParent(Node *node, Node *parent, Node *newParent) {
    if (!parent) root = newParent;
    else if (parent->left == node) parent->left = newParent;
    else parent->right = newParent;
    if (newParent) newParent->parent = parent;
}

void AVLTree::visualizeTree(const string &outputFilename) {
    ofstream outFS(outputFilename.c_str());
    if (!outFS.is_open()) {
        cout << "Error" << endl;
        return;
    }
    outFS << "digraph G {" << endl;
    visualizeTree(outFS, root);
    outFS << "}";
    outFS.close();
}

void AVLTree::visualizeTree(ofstream &outFS, Node *n) {
    if (n) {
        outFS << n->value << " [layer=" << '"' << n->height() << '"' << "]" << endl;
        if (n->left) visualizeTree(outFS, n->left);
        else outFS << n->value << " -> " << n->value << "_LNULL" << ";" << endl;
        if (n->parent) outFS << n->value << " -> " << n->parent->value << ";" << endl;
        if (n->right) visualizeTree(outFS, n->right);
        else outFS << n->value << " -> " << n->value << "_RNULL" << ";" << endl;
    }
}
