#include "HashTable.h" // Include the header file for the HashTable class
#include "WordEntry.h" // Include the header file for the WordEntry class
#include <fstream> // Include the header file for file input/output operations
#include <iostream> // Include the header file for input/output operations

// Constructor for HashTable class
HashTable::HashTable(int s) {
    size = s; // Set the size of the hash table
    hashTable = new list<WordEntry>[size]; // Dynamically allocate memory for the hash table
}

// Method to compute the hash value for a given string
int HashTable::computeHash(const string &s) const {
    int hash = 0; // Initialize the hash value to zero
    for (char c : s) { // Iterate through each character of the string
        hash += c; // Add the ASCII value of the character to the hash value
    }
    return hash % size; // Return the hash value modulo the size of the hash table
}

// Method to insert a word and its score into the hash table
void HashTable::put(const string &s, int score) {
    int index = computeHash(s); // Compute the hash value for the given string
    for (auto it = hashTable[index].begin(); it != hashTable[index].end(); ++it) {
        // Check if the word already exists in the hash table
        if (it->getWord() == s) {
            it->addNewAppearance(score); // If yes, update its appearance with the new score
            return;
        }
    }
    // If the word is not found in the hash table, add it as a new entry
    WordEntry newEntry(s, score);
    hashTable[index].push_back(newEntry);
}

// Method to get the average score of appearances for a given word
double HashTable::getAverage(const string &s) const {
    int index = computeHash(s); // Compute the hash value for the given string
    for (const WordEntry &entry : hashTable[index]) {
        // Iterate through the entries in the bucket at the computed hash index
        if (entry.getWord() == s) { // Check if the word matches the given word
            return entry.getAverage(); // If yes, return its average score
        }
    }
    return 2.0; // Default neutral result if the word is not found
}

// Method to check if a given word exists in the hash table
bool HashTable::contains(const string &s) const {
    int index = computeHash(s); // Compute the hash value for the given string
    for (const WordEntry &entry : hashTable[index]) {
        // Iterate through the entries in the bucket at the computed hash index
        if (entry.getWord() == s) { // Check if the word matches the given word
            return true; // If yes, return true indicating that the word exists in the hash table
        }
    }
    return false; // If the word is not found, return false
}



int main() {
    // Declare variables for input data
    string line; // To store each line of the input file
    int score; // To store the score of each review
    string message = " "; // To store the user's movie review

    // Open input file
    ifstream myfile("movieReviews.txt");
    if (myfile.fail()) { // Check if file opening failed
        cout << "could not open file" << endl;
        exit(1); // Exit the program with error code 1
    }

    // Create hash table
    HashTable table(20071); // Initialize a hash table with size 20071

    // Read data from input file and insert into hash table
    while (!myfile.eof()) { // Continue until end of file is reached
        myfile >> score; // Read score
        myfile.get(); // Read blank space
        getline(myfile, line); // Read the rest of the line
        int len = line.size(); // Get the length of the line
        while (len > 0) { // Process individual words in the line
            string sub; // To store each word
            len = line.find(" "); // Find the position of the next space
            if (len > 0) { // If space is found
                sub = line.substr(0, len); // Extract the word
                line = line.substr(len + 1, line.size()); // Update the line
            }
            else { // If no space is found
                sub = line.substr(0, line.size() - 1); // Extract the last word
            }
            table.put(sub, score); // Insert the word with its score into the hash table
        }
    }

    // Prompt the user for a new movie review
    while (message.length() > 0) { // Continue until the user enters an empty review
        cout << "enter a review -- Press return to exit: " << endl;
        getline(cin, message); // Read the user's input

        // Variables for calculating the average sentiment score
        double sum = 0; // Sum of scores
        int count = 0; // Number of words

        double sentiment = 0.0; // Overall sentiment score

        size_t len = message.size(); // Get the length of the input message
        // Process individual words in the input message
        while (len != string::npos) { // Continue until no more words are found
            string sub; // To store each word
            len = message.find(" "); // Find the position of the next space
            if (len != string::npos) { // If space is found
                sub = message.substr(0, len); // Extract the word
                message = message.substr(len + 1, message.size()); // Update the message
            }
            else { // If no space is found
                sub = message; // Extract the last word
            }
            // Calculate the sentiment score of each word and accumulate
            sum += table.getAverage(sub); // Get the average score of the word from the hash table
            ++count; // Increment the word count
        }

        if (message.size() > 0) { // If the user entered a non-empty review
            sentiment = sum / count; // Calculate the overall sentiment score
            cout << "The review has an average value of " << sentiment << endl;
            // Determine sentiment label based on the sentiment score
            if (sentiment >= 3.0) {
                cout << "Positive Sentiment" << endl;
            }
            else if (sentiment >= 2.0) {
                cout << "Somewhat Positive Sentiment" << endl;
            }
            else if (sentiment >= 1.0) {
                cout << "Somewhat Negative Sentiment" << endl;
            }
            else {
                cout << "Negative Sentiment" << endl;
            }
            cout << endl; // Add a new line for clarity
        }
    }

    return 0; // Return 0 to indicate successful completion of the program
}
