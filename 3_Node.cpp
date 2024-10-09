#include "Node.h"

// Constructor for the Node class
Node::Node() : left(nullptr), middle(nullptr), right(nullptr), parent(nullptr) { }

// Function to check if node has two strings
bool Node::hasTwoStrings() const
{
    // returns true if the string is not empty 
    return !large.empty();
}
