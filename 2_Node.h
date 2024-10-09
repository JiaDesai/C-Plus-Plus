#include <string>

using namespace std;

class Node {
public:
    string data;    // Data stored in the node (string)
    int count;      // Count of occurrences of the data
    Node *left;     // Pointer to the left child node
    Node *right;    // Pointer to the right child node

    // Constructor
    Node(const string &data) : data(data), count(1), left(nullptr), right(nullptr) {}
};
