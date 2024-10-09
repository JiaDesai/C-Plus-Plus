#ifndef ARITHMETICEXPRESSION_H
#define ARITHMETICEXPRESSION_H

#include <sstream>   // For stringstream
#include <fstream>   // For file stream operations
#include <stack>     // For stack data structure
#include <iostream>  // For standard input/output operations
#include <cstdlib>   // For standard library functions like exit()
#include <string>    // For string operations

using namespace std;

// TreeNode struct representing a node in the arithmetic expression tree
struct TreeNode{
    char data;       // Data stored in the node
    char key;        // Key for identifying the node
    TreeNode* left;  // Pointer to the left child
    TreeNode* right; // Pointer to the right child
    TreeNode(char data, char key): data(data), key(key), left(0), right(0) {} // Constructor
};

// Class representing an arithmetic expression
class arithmeticExpression {
  private:
    string infixExpression; // Infix expression string
    TreeNode* root;        // Pointer to the root node of the expression tree

  public:
    /* Constructor:
       Initializes an empty tree and sets the infixExpression
       to the value of parameter passed in. */
    arithmeticExpression(const string &);

    /* Destructor (optional):
       Deallocates all the nodes in the tree. */
    ~arithmeticExpression();

    /* Converts the infixExpression to its equivalent postfix string
       and then generates the tree and assigns the root node to the 
       root data field. The key for the first node is 'a', 'b' for the second node and so on. */
    void buildTree();

    /* Calls the recursive infix function. */
    void infix();

    /* Calls the recursive prefix function. */
    void prefix();

    /* Calls the recursive postfix function. */
    void postfix();

    /* Calls the recursive visualizeTree function and generates the .png file using system call. */
    void visualizeTree(const string &);

 private:
    /* Helper function that returns an integer according to
       the priority of the given operator. */
    int priority(char);

    /* Helper function that returns the postfix notation equivalent
       to the given infix expression */
    string infix_to_postfix();

    /* Helper function that outputs the infix notation of the arithmetic expression tree
       by performing the inorder traversal of the tree.
       An opening and closing parenthesis must be added at the 
       beginning and ending of each expression. */
    void infix(TreeNode *);

    /* Helper function that outputs the prefix notation of the arithmetic expression tree
       by performing the preorder traversal of the tree. */
    void prefix(TreeNode *);

    /* Helper function that outputs the postfix notation of the arithmetic expression tree
       by performing the postorder traversal of the tree. */
    void postfix(TreeNode *);

    /* Helper function for generating the dotty file. This is a recursive function. */
    //void visualizeTree(ofstream &, TreeNode *);

    /* Recursive helper function to build the tree from a postfix expression */
    TreeNode* buildTreeHelper(string &, char); 

    /* Recursive helper function to delete all nodes in the tree */
    void destructorHelper(TreeNode*); 
};

#endif
