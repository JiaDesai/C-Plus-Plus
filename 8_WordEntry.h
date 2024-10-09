#pragma once // Include guard to ensure this header is only included once during compilation

#include <string> // Include the header for string operations
#include <vector> // Include the header for vector operations
#include <iostream> // Include the header for input and output operations

using namespace std; // Use the standard namespace for convenience

class WordEntry { // Declaration of the WordEntry class

 private:
	string word; // Private member variable to store the word
	int numAppearances; // Private member variable to store the number of appearances
	int totalScore; // Private member variable to store the total score

 public:
	// Constructor for WordEntry class, initializes word and numAppearances
	WordEntry(const string &, int);
	
	// Method to add a new appearance of the word with a given score
	void addNewAppearance(int);
	
	// Method to get the word stored in the WordEntry object
	const string & getWord() const;
	
	// Method to calculate and return the average score of the word appearances
	double getAverage() const;
};
