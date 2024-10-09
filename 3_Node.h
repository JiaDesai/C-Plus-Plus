#ifndef __NODE_H__
#define __NODE_H__

#include <string>

using namespace std; 

class Node
{
    //declare Tree class as a friend so it can access the private members
    friend class Tree;

  private:
    string small;
    string large;

    // pointers to the children or parent nodes
    Node *left;
    Node *middle;
    Node *right;
    Node *parent;

    // private constructor for Node class
    Node();
    bool hasTwoStrings() const;
};

#endif
