#pragma once // Include guard to ensure this header is only included once during compilation

#include <string> // Include the header for string operations
#include <list> // Include the header for list operations
#include <iostream> // Include the header for input and output operations
#include "WordEntry.h" // Include the header file for the WordEntry class

using namespace std; // Use the standard namespace for convenience

class HashTable { // Declaration of the HashTable class

 private:
	list<WordEntry> *hashTable; // Pointer to an array of lists of WordEntry objects
	int size; // Size of the hash table

 public:
	// Constructor for HashTable class
	HashTable(int size);
	
	// Method to check if a word exists in the hash table
	bool contains(const string& word) const;
	
	// Method to get the average score of a word in the hash table
	double getAverage(const string& word) const;
	
	// Method to insert a new word with its score into the hash table
	void put(const string& word , int score);
 
 private:
	// Private method to compute the hash value of a word
	int computeHash(const string &) const;
};
