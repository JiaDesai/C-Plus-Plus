#include "Tree.h"

#include <iostream>

using namespace std; 

// Constructor for the Tree class
Tree::Tree()
{
    root = nullptr;
}

// Destructor for the Tree class 
Tree::~Tree()
{
    delete recurDelete(root); // recursivly delete all nodes in the tree
}

// Function to insert a new node into the tree
void Tree::insert(const string &str) 
{
    // if tree is empty, create a root node
    if (!root)
    {
        root = new Node();
        root->small = str;
    }
    else
    {
        Node* targetNode = root;
        while (targetNode->left)
        {
            // If the current node has two strings, proceed accordingly
            if (targetNode->hasTwoStrings())
            {
                if (targetNode->small > str)
                {
                    targetNode = targetNode->left;
                }
                else if (targetNode->large < str)
                {
                    targetNode = targetNode->right;
                }
                else
                {
                    targetNode = targetNode->middle;
                }
            }
            else
            {
                // If the current node has only one string, proceed accordingly
                if (targetNode->small > str)
                {
                    targetNode = targetNode->left;
                }
                else
                {
                    targetNode = targetNode->middle;
                }
            }
        }

        // If the current node has two strings, perform a split
        if (targetNode->hasTwoStrings())
        {
           // Variables to store the small, middle, and large strings
            string small;
            string middle;
            string large;

            if (targetNode->small > str)
            {
                small = str;
                middle = targetNode->small;
                large = targetNode->large;
            }
            else
            {
                small = targetNode->small;

                if (targetNode->large < str)
                {
                    middle = targetNode->large;
                    large = str;
                }
                else
                {
                    middle = str;
                    large = targetNode->large;
                }
            }

            // Create a new node for the small and large strings
            Node* smallNode = new Node();
            smallNode->small = small;
            Node* largeNode = new Node();
            largeNode->small = large;

            // Set the left and right pointers of the new nodes to the current node
            targetNode->small = middle;
            targetNode->large = ""; 
            targetNode->left = smallNode;
            targetNode->middle = largeNode;
            targetNode->right = nullptr; 

            // update parent pointer
            smallNode->parent = targetNode;
            largeNode->parent = targetNode;

            // perform shift up
            shiftUp(targetNode);
        }
        else
        {
            // if target only has one string, insert new string
            if (targetNode->small > str)
            {

                targetNode->large = targetNode->small;
                targetNode->small = str;
            }
            else
            {
                // Put str in the large area
                targetNode->large = str;
            }
        }
    }
}
// Function to perform a pre-order traversal of the tree
void Tree::preOrder() const
{
    preOrder(root);
}
// Function to perform a in-order traversal of the tree
void Tree::inOrder() const
{
    inOrder(root);
}
// Function to perform a post-order traversal of the tree
void Tree::postOrder() const
{
    postOrder(root);
}

// Function to remove a string from a tree
void Tree::remove(const string &str)
{
    Node* searchNode = root;
    while (searchNode)
    {
        // search for the string in the tree
        if (searchNode->small == str || (searchNode->hasTwoStrings() && searchNode->large == str))
        {
            break;
        }
        else 
        {
            // navigate through the string based string values
            if (searchNode->small > str)
            {

                searchNode = searchNode->left;
            }
            else
            {
                if (searchNode->hasTwoStrings() && searchNode->large < str)
                {

                    searchNode = searchNode->right;
                }
                else
                {

                    searchNode = searchNode->middle;
                }
            }
        }
    }

    
    if (searchNode)
    {
        // If the node has two strings, remove
        if (searchNode->hasTwoStrings())
        {
            if (str == searchNode->small)
            {
                searchNode->small = searchNode->large;
                searchNode->large = "";
            }
            else
            {
                searchNode->large = "";
            }
        }
        else
        {
            Node* parent = searchNode->parent;
            if (parent) {
                //update parent node when string is removed
                if (str < parent->small) {
                    parent->left = nullptr;
                    parent->large = parent->middle->small;
                    parent->middle = nullptr;
                } else {
                    parent->middle = nullptr;
                    parent->large = parent->small;
                    parent->small = parent->left->small;
                    parent->left = nullptr;
                }
            }
            else
            {
                // if the root node is being removed
                Node* temp = new Node();
                if (root->left) {
                    temp->small = root->left->small;
                    temp->large = root->middle->small;
                    root = temp;
                } else {
                    root = nullptr;
                }
            }
        }
    }
}

// Function to search for a string in a tree
bool Tree::search(const string &str) const
{
    Node* searchNode = root;
    while (searchNode)
    {

        // search for the string in the tree
        if (searchNode->small == str || (searchNode->hasTwoStrings() && searchNode->large == str))
        {
            return true;
        }
        else 
        {
            // navigate through the tree based on string values
            if (searchNode->small > str)
            {

                searchNode = searchNode->left;
            }
            else
            {
                if (searchNode->hasTwoStrings() && searchNode->large < str)
                {

                    searchNode = searchNode->right;
                }
                else
                {

                    searchNode = searchNode->middle;
                }
            }
        }
    }

    return false;
}

// Function to perform shifting in the tree
void Tree::shiftUp(Node *node)
{

    if (node->parent)
    {
        Node* parent = node->parent;
        if (parent->hasTwoStrings()) 
        {
            // if the parent has two strings, perform shifting up accordingly
            if (parent->small > node->small) 
            {
                Node* newLarge = new Node();
                newLarge->left = parent->middle;
                newLarge->left->parent = newLarge;
                newLarge->middle = parent->right;
                newLarge->middle->parent = newLarge;
                newLarge->small = parent->large;


                parent->left = node; 
                parent->middle = newLarge;
                parent->right = nullptr;
                parent->large = ""; 


                newLarge->parent = parent;
            }
            else if (parent->large < node->small) 
            {
                Node* newSmall = new Node();

                newSmall->left = parent->left;
                newSmall->left->parent = newSmall;
                newSmall->middle = parent->middle;
                newSmall->middle->parent = newSmall;
                newSmall->small = parent->small;


                parent->left = newSmall;
                parent->middle = node; 
                parent->right = nullptr;
                parent->small = parent->large;
                parent->large = ""; 

                newSmall->parent = parent;
            }
            else 
            {
                Node* newSmall = new Node();
                newSmall->small = parent->small;
                newSmall->left = parent->left;
                newSmall->left->parent = newSmall;
                newSmall->middle = node->left;
                newSmall->middle->parent = newSmall;

                Node* newLarge = new Node();
                newLarge->small = parent->large;
                newLarge->left = node->middle;
                newLarge->left->parent = newLarge;
                newLarge->middle = parent->middle;
                newLarge->middle->parent = newLarge;


                parent->left = newSmall;
                parent->middle = newLarge;
                parent->right = nullptr;
                parent->small = node->small;
                parent->large = ""; 


                newSmall->parent = parent;
                newLarge->parent = parent;

                // delete old node
                delete node; 
            }

            // perform shift up 
            shiftUp(parent);
        }
        else 
        {
            // If the parent has one string, perform shifting up accordingly
            if (parent->small > node->small) 
            {
                parent->large = parent->small;
                parent->small = node->small;

                parent->left = node->left;
                parent->right = parent->middle;
                parent->middle = node->middle;
            }
            else 
            {
                parent->large = node->small;


                parent->middle = node->left;
                node->left->parent = parent;
                parent->right = node->middle;
                node->middle->parent = parent;
            }


            node->left->parent = parent;
            node->middle->parent = parent;
            // delete old node
            delete node;
        }
    }
}

// Recursive function to delete nodes in a post-order traversal manner
Node *Tree::recurDelete(Node *node)
{
    if (node)
    {
        delete recurDelete(node->left);
        delete recurDelete(node->middle);
        delete recurDelete(node->right);
    }

    return node;
}

// Recursive function to perform pre-order traversal of the tree
void Tree::preOrder(Node *node) const
{
    if (node)
    {
        if (node->hasTwoStrings())
        {
            // If the node has two strings, print them and traverse the children
            cout << node->small << ", ";
            preOrder(node->left);
            cout << node->large << ", ";
            preOrder(node->middle);
            preOrder(node->right);
        }
        else
        {
            // If the node has one string, print it and traverse the children
            cout << node->small << ", ";
            preOrder(node->left);
            preOrder(node->middle);
        }
    }
}

// Recursive function to perform in-order traversal of the tree
void Tree::inOrder(Node *node) const
{
    if (node)
    {  
         // Traverse the left child, print the string, traverse the middle child
        inOrder(node->left);
        cout << node->small << ", ";
        inOrder(node->middle);

         // If the node has two strings, print the large string and traverse the right child
        if (node->hasTwoStrings())
        {
            cout << node->large << ", ";
            inOrder(node->right);
        }
    }
}

// Recursive function to perform post-order traversal of the tree
void Tree::postOrder(Node *node) const
{
    if (node)
    {
        if (node->hasTwoStrings())
        {

            postOrder(node->left);
            postOrder(node->middle);
            cout << node->small << ", ";
            postOrder(node->right);
            cout << node->large << ", ";
        }
        else
        {
            postOrder(node->left);
            postOrder(node->middle);
            cout << node->small << ", ";
        }
    }
}
