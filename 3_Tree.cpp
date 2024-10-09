#ifndef __TREE_H__
#define __TREE_H__

#include "Node.h"

class Tree
{
  private:
    // pointer to the root node of the tree
    Node *root;
  public:
    Tree(); // constructor
    ~Tree(); // destructor
    // functions
    void insert(const string &);
    void preOrder() const;
    void inOrder() const;
    void postOrder() const;
    void remove(const string &); 
    bool search (const string &) const;
    void shiftUp(Node*);
  private:
    // recursive functions 
    Node* recurDelete(Node*);
    void preOrder(Node*) const; 
    void inOrder(Node*) const;
    void postOrder(Node*) const; 
};

#endif
