#include "Node.h"

#include <string>

using namespace std;

class AVLTree
{
  private:
    Node *root;

  public:
    AVLTree() : root(nullptr){};
    ~AVLTree();
    void insert(const string &);
    int balanceFactor(Node *) const;
    void printBalanceFactors() const;
    void visualizeTree(const string &);

private:
    Node *findUnbalancedNode(Node *) const;
    void rotate(Node *);
    void rotateLeft(Node *);
    void rotateRight(Node *);
    void recursiveDelete(Node *);
    void printBalanceFactors(Node *) const;
    void visualizeTree(ofstream &, Node *);
    void updateParent(Node* node, Node* parent, Node* newParent);
};
