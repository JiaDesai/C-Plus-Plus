#include <string>

using namespace std;

class Node
{
    friend class AVLTree;

  private:
    string value;
    Node *parent;
    Node *left;
    Node *right;

  public:
    Node(const string &newValueString, Node *newParentPtr)
        : value(newValueString), parent(newParentPtr), left(nullptr), right(nullptr){};
    int getBalanceFactor() const;
    int leftSubTreeHeight() const;
    int rightSubTreeHeight() const;
    int height() const;
};
