#include <iostream>

using namespace std;

// Node class definition
class Node {
public:
    string data; // Data stored in the node (string)
    int count;   // Count of occurrences of the data
    Node *left;  // Pointer to the left child node
    Node *right; // Pointer to the right child node
    
    // Constructor
    Node(const string &data) : data(data), count(1), left(nullptr), right(nullptr) {}
};

// Default constructor
BSTree::BSTree() : root(nullptr) {}

// Destructor (calls a helper function to delete all nodes)
BSTree::~BSTree() {
    // Call a helper function to delete all nodes
    // This function will be recursive
    // Pass root as the starting point
    destroyTree(root);
}

// Helper function for destructor (recursive)
void BSTree::destroyTree(Node* node) {
    if (node != nullptr) {
        // Recursively delete left and right subtrees
        destroyTree(node->left);
        destroyTree(node->right);
        // Delete the current node
        delete node;
    }
}

// Insert function
void BSTree::insert(const string &newString) {
    root = insertRecursive(root, newString);
}

// Recursive helper function for insert
Node* BSTree::insertRecursive(Node* node, const string &newString) {
    // If the tree is empty, create a new node and return it
    if (node == nullptr) {
        return new Node(newString);
    }
    
    // If the newString is smaller than the current node's data, insert into the left subtree
    if (newString < node->data) {
        node->left = insertRecursive(node->left, newString);
    }
    // If the newString is greater than the current node's data, insert into the right subtree
    else if (newString > node->data) {
        node->right = insertRecursive(node->right, newString);
    }
    // If the newString is equal to the current node's data, increment count
    else {
        node->count++;
    }
    
    // Return the modified node
    return node;
}

// Remove function
void BSTree::remove(const string &key) {
    root = removeRecursive(root, key);
}

// Recursive helper function for remove
Node* BSTree::removeRecursive(Node* node, const string &key) {
    // Base case: if the tree is empty
    if (node == nullptr) {
        return nullptr;
    }
    
    // If the key is smaller than the current node's data, go to the left subtree
    if (key < node->data) {
        node->left = removeRecursive(node->left, key);
    }
    // If the key is greater than the current node's data, go to the right subtree
    else if (key > node->data) {
        node->right = removeRecursive(node->right, key);
    }
    // If the key is found
    else {
        // If the count of the key is greater than 1, decrement count
        if (node->count > 1) {
            node->count--;
        }
        // If the count of the key is 1, remove the node
        else {
            // Case 1: If the node is a leaf node or has only one child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            
            // Case 2: If the node has two children
            // Find the inorder successor (smallest in the right subtree)
            Node* temp = minValueNode(node->right);
            // Copy the inorder successor's data to this node
            node->data = temp->data;
            // Remove the inorder successor
            node->right = removeRecursive(node->right, temp->data);
        }
    }
    
    // Return the modified node
    return node;
}

// Helper function to find the node with the smallest value in a subtree
Node* BSTree::minValueNode(Node* node) {
    // Keep going to the left to find the smallest value
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Search function
bool BSTree::search(const string &key) const {
    return searchRecursive(root, key);
}

// Recursive helper function for search
bool BSTree::searchRecursive(Node* node, const string &key) const {
    // Base case: if the tree is empty or key is not found
    if (node == nullptr) {
        return false;
    }
    
    // If key is smaller than current node's data, go to left subtree
    if (key < node->data) {
        return searchRecursive(node->left, key);
    }
    // If key is greater than current node's data, go to right subtree
    else if (key > node->data) {
        return searchRecursive(node->right, key);
    }
    // If key is found
    else {
        return true;
    }
}

// Largest function
string BSTree::largest() const {
    if (root == nullptr) {
        return ""; // Return empty string if tree is empty
    }
    // Keep going to the right to find the largest value
    Node* current = root;
    while (current->right != nullptr) {
        current = current->right;
    }
    return current->data;
}

// Smallest function
string BSTree::smallest() const {
    if (root == nullptr) {
        return ""; // Return empty string if tree is empty
    }
    // Keep going to the left to find the smallest value
    Node* current = root;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current->data;
}

// Height function
int BSTree::height(const string &key) const {
    return heightRecursive(root, key);
