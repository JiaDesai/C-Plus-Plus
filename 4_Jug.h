#ifndef __JUG_H__
#define __JUG_H__

#include <list>
#include <string>
#include <vector>

using namespace std;

// Class representing a vertex in the graph
class Vertex
{
  public:
    string key;
    list<pair<int, int>> neighbors; 
    Vertex(string key) : key(key) { } // Constructor
    ~Vertex() { } // Destructor
};

// Class representing the Jug problem and solution
class Jug
{
  private:
    int Ca;   // Capacity of Jug A
    int Cb;   // Capacity of Jug B
    int N;    
    int cfA;  // Cost to fill A
    int cfB;  // Cost to fill B
    int ceA;  // Cost to empty A
    int ceB;  // Cost to empty B
    int cpAB; // Cost to pour from A to B
    int cpBA; // Cost to pour from B to A
    vector<Vertex> graph; 
  public:
    // Constructor with parameters to initialize the Jug
    Jug(int, int, int, int, int, int, int, int, int);
    // Destructor
    ~Jug();

    // Solve method to find the solution and store it in the provided string
    int solve(string&);
  
private:
    // Check if input values are valid
    bool isValidInputs() const;
    bool isCorrectAmount(list<pair<int, int>>);
    // Process the input string and update the vector of steps
    int processString(vector<int>&, string&) const;
    // Process the total cost of a solution
    int processTotalCost(vector<int> steps);
    vector<int> attempt();
    int doStep(int&, int&, const int&);
    vector<int> traverse(int, vector<int>, list<pair<int, int>>);
    // Check if a cycle is encountered in the traversal
    bool checkIfCycled(int, int, list<pair<int, int>>);
};

#endif
