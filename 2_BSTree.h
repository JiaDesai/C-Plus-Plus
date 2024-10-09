#ifndef BSTREE_H
#define BSTREE_H
#include "Node.h"
#include <iostream>
#include <string>
using namespace std;

class BSTree {
    public:
       // public member functions 
        BSTree();
       ~BSTree();
       BSTree(const BSTree& copy);
       BSTree& operator=(const BSTree& rhs);

       // Basic insert, search, find and remove operations
       void insert(const string&);
       bool search(const string&) const;
       string largest() const;
       string smallest() const;
       int height(const string&) const;
       void remove(const string&);
       void preOrder() const;
       void inOrder() const;
       void postOrder() const;

    private:
        // Pointer to root of BST
        Node* root;

        // private helper functions
        bool search(Node*, const string&) const;
        void helpInsert(Node*, const string&);
        Node* searchNode(Node*, const string&) const;
        int nodeHeight(const Node*) const;
        Node* helpCopy(const Node*);
        void helpRemove(const string& val);
        void inOrder(Node*) const;
        void preOrder(Node*) const;
        void postOrder(Node*) const;
};


#endif
