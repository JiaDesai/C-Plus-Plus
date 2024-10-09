#include <iostream>
#include <limits>
#include "BSTree.h" // Include the header file where BSTree class is defined

using namespace std;

// Function to print the preorder, inorder, and postorder traversal of the tree
void printOrders(BSTree *tree) {
  cout << "Preorder = ";
  tree->preOrder();
  cout << endl << "Inorder = ";
  tree->inOrder();
  cout << endl << "Postorder = ";
  tree->postOrder();
  cout << endl;
}

// Function to display the menu and get user choice
int menu() {
  int choice = 0;
  cout << endl << "Enter menu choice: ";
  cout << endl;
  cout 
    << "1. Insert" << endl
    << "2. Remove" << endl
    << "3. Print" << endl
    << "4. Search" << endl
    << "5. Smallest" << endl
    << "6. Largest" << endl
    << "7. Height" << endl
    << "8. Quit" << endl;
  cin >> choice;
  
  // Fix buffer just in case non-numeric choice entered
  // Also gets rid of newline character
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  return choice;
}

int main( ) {
    
    BSTree tree; // Create an instance of the BSTree class

    int choice = menu(); // Get initial user choice

    string entry;
  
    // Main loop for menu-driven program
    while (choice != 8) {
    
        if (choice == 1) {
          cout << "Enter string to insert: ";
          getline(cin, entry);
          tree.insert(entry); // Insert the entered string into the tree
        } else if (choice == 2) {
          cout << "Enter string to remove: ";
          getline(cin, entry);
          tree.remove(entry); // Remove the entered string from the tree
        } else if (choice == 3) {
          printOrders(&tree); // Print the traversal orders of the tree
        } else if (choice == 4) {
          cout << "Enter string to search for: ";
          getline(cin, entry);
          // Search for the entered string in the tree
          if (tree.search(entry)) {
              cout << "Found " << entry << endl;
          } else {
              cout << "Not Found " << entry << endl;
          }
        } else if (choice == 5) {
          // Print the smallest string in the tree
          cout << "Smallest: " << tree.smallest() << endl;
        } else if (choice == 6) {
          // Print the largest string in the tree
          cout << "Largest: " << tree.largest() << endl;
        } else if (choice == 7) {
          cout << "Enter string: ";
          getline(cin, entry);
          // Print the height of the entered string in the tree
          cout << "Height of " << entry << ": " << tree.height(entry) << endl;
        }
        // Get user choice again
        choice = menu();
    }
    return 0;
}
