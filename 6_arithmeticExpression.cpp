#include "arithmeticExpression.h"
#include <sstream>  // For stringstream
#include <fstream>  // For file stream operations
#include <stack>    // For stack data structure
#include <iostream> // For standard input/output operations
#include <cstdlib>  // For standard library functions like exit()
#include <string>   // For string operations

using namespace std;

// Constructor initializes an empty tree and sets the infixExpression
arithmeticExpression::arithmeticExpression(const string &s) {
  root = nullptr;
  infixExpression = s;
}

// Destructor calls a recursive function to delete all nodes
arithmeticExpression::~arithmeticExpression() {
  destructorHelper(root);
}

// Recursive helper function to delete all nodes in the tree
void arithmeticExpression::destructorHelper(TreeNode* node) {
  if (node != nullptr) {
    destructorHelper(node->left);
    destructorHelper(node->right);
    delete node;
  }
}

// Builds the expression tree from the infix expression
void arithmeticExpression::buildTree() {
  string s = infix_to_postfix(); // Convert infix to postfix
  root = buildTreeHelper(s, 'a'); // Build tree from postfix expression
}

// Recursive helper function to build the tree from a postfix expression
TreeNode* arithmeticExpression::buildTreeHelper(string & s, char key) {
  if (s.size() > 0) {
    TreeNode* current = new TreeNode((s.at(s.length() - 1)), key);
    key++;
    s.pop_back();

    if (priority(current->data) > 0) {
      current->right = buildTreeHelper(s, key);
      current->left = buildTreeHelper(s, key);
    }
    return current;
  }
  return nullptr;
}

// Prints the infix expression
void arithmeticExpression::infix() {
  infix(root);
}

// Prints the prefix expression
void arithmeticExpression::prefix() {
  prefix(root);
}

// Prints the postfix expression
void arithmeticExpression::postfix() {
  postfix(root);
}

// Returns the priority of an operator
int arithmeticExpression::priority(char op) {
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

// Converts infix expression to postfix expression
string arithmeticExpression::infix_to_postfix(){
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

// Prints infix expression recursively
void arithmeticExpression::infix(TreeNode* expression) {
  if (expression != nullptr) {
    if (expression->left != nullptr) {
      cout << "(";
    }

    infix(expression->left);
    cout << expression->data;
    infix(expression->right);

    if (expression->left != nullptr) {
      cout << ")";
    }
  }
}

// Prints prefix expression recursively
void arithmeticExpression::prefix(TreeNode* expression) {
  if (expression != nullptr) {
    cout << expression->data;
    prefix(expression->left);
    prefix(expression->right);
  }
}

// Prints postfix expression recursively
void arithmeticExpression::postfix(TreeNode* expression) {
  if (expression != nullptr) {
    postfix(expression->left);
    postfix(expression->right);
    cout << expression->data;
  }
}
