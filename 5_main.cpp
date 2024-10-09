#include "Heap.h"

using namespace std;

// Function to display the menu and get user's choice
int menu() {
  int choice = 0;
  cout << endl << "Enter menu choice: ";
  cout << endl;
  cout 
    << "1. Enqueue" << endl
    << "2. Print" << endl
    << "3. Dequeue" << endl
    << "4. Quit" << endl;
  cin >> choice;

  // Fix buffer just in case a non-numeric choice is entered
  // Also gets rid of the newline character
  cin.clear();
  cin.ignore(256, '\n');
  return choice;
}

int main(){
    // Create a max heap object
    Heap max_heap;

    // Get user's choice from the menu
    int choice = menu();

    // Continue looping until user chooses to quit
    while (choice != 4) {

    if (choice == 1) {
      int priority, jobNumber, numPages;
      cout << "Enter print job to enqueue (priority, job Number, number of pages): ";
      cin>>priority>>jobNumber>>numPages;
      cout << endl;

      // Enqueue a new print job into the heap
      max_heap.enqueue(new PrintJob(priority, jobNumber, numPages));

    } 
    else if (choice == 2) {
      // Print the highest priority job in the heap
      max_heap.print();
    }
    else if (choice == 3) {
        // Dequeue the highest priority job from the heap
        max_heap.dequeue();
    }
    // Get user's choice from the menu again
    // Fix buffer just in case a non-numeric choice is entered
    choice = menu();
    }
    return 0;
}
