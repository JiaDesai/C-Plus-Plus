#include "Tree.h" 
#include <iostream>

using namespace std;

// Function to print the pre-order, in-order, and post-order traversals of the tree.
void printOrders(Tree *tree) {
  cout << "Preorder = ";
  tree->preOrder();   // Print pre-order traversal.
  cout << endl;
  cout << "Inorder = ";
  tree->inOrder();    // Print in-order traversal.
  cout << endl;
  cout << "Postorder = ";
  tree->postOrder();  // Print post-order traversal.
  cout << endl;
}

// Function to display the menu and get user's choice.
int menu() {
  int choice = 0;
  cout << endl << "Enter menu choice: ";
  cout << endl;
  cout 
    << "1. Insert" << endl
    << "2. Remove" << endl
    << "3. Print" << endl
    << "4. Search" << endl
    << "5. Quit" << endl;
  cin >> choice;

  // Fix buffer just in case a non-numeric choice is entered.
  // Also gets rid of the newline character.
  cin.clear();
  cin.ignore(256, '\n');
  return choice;
}

int main( ) {

  Tree tree;   // Create a Tree object.

  int choice = menu();  // Get the initial choice from the user.

  string entry;

  // Loop to interact with the user until the user chooses to quit (choice 5).
  while (choice != 5) {
    if (choice == 1) {
      cout << "Enter movie title to insert: ";
      getline(cin, entry);
      cout << endl;

      tree.insert(entry);  // Insert the entered movie title into the tree.

    } else if (choice == 2) {
      cout << "Enter movie title to remove: ";
      getline(cin, entry);
      cout << endl;

      tree.remove(entry);  // Remove the entered movie title from the tree.

    } else if (choice == 3) {
      printOrders(&tree);  // Print the traversals of the tree.

    } else if (choice == 4) {
      cout << "Enter movie title to search for: ";
      getline(cin, entry);
      cout << endl;

      // Search for the entered movie title in the tree and display the result.
      if (tree.search(entry)) {
        cout << "Found" << endl;
      } else {
        cout << "Not Found" << endl;
      }
    }

    // Fix buffer just in case a non-numeric choice is entered.
    choice = menu();  // Get the next choice from the user.
  }

  return 0;
}
