#include "Jug.h"
#include <iostream>
#include <sstream>

using namespace std;

// Constructor for the Jug class
Jug::Jug(int Ca, int Cb, int N, int cfA, int cfB, int ceA, int ceB, int cpAB, int cpBA) :
    Ca(Ca), Cb(Cb), N(N), cfA(cfA), cfB(cfB), ceA(ceA), ceB(ceB), cpAB(cpAB), cpBA(cpBA) {
    // Generate the graph with vertices and their neighbors
    Vertex cfA_v("cfA");   // Vertex representing filling A
    Vertex cfB_v("cfB");   // Vertex representing filling B
    Vertex ceA_v("ceA");   // Vertex representing emptying A
    Vertex ceB_v("ceB");   // Vertex representing emptying B
    Vertex cpAB_v("cpAB"); // Vertex representing pouring A to B
    Vertex cpBA_v("cpBA"); // Vertex representing pouring B to A

    // Define edges and associated costs for each vertex
    // Each vertex has edges to its possible next states and associated costs
    cfA_v.neighbors.push_back(pair<int, int>(1, cfB));  // Fill A -> Move to filling B, cost = cfB
    cfA_v.neighbors.push_back(pair<int, int>(4, cpAB)); // Fill A -> Move to pouring A to B, cost = cpAB

    cfB_v.neighbors.push_back(pair<int, int>(0, cfA));  // Fill B -> Move to filling A, cost = cfA
    cfB_v.neighbors.push_back(pair<int, int>(5, cpBA)); // Fill B -> Move to pouring B to A, cost = cpBA

    ceA_v.neighbors.push_back(pair<int, int>(1, cfB));  // Empty A -> Move to filling B, cost = cfB
    ceA_v.neighbors.push_back(pair<int, int>(3, ceB));  // Empty A -> Move to emptying B, cost = ceB
    ceA_v.neighbors.push_back(pair<int, int>(5, cpBA)); // Empty A -> Move to pouring B to A, cost = cpBA

    ceB_v.neighbors.push_back(pair<int, int>(0, cfA));  // Empty B -> Move to filling A, cost = cfA
    ceB_v.neighbors.push_back(pair<int, int>(2, ceA));  // Empty B -> Move to emptying A, cost = ceA
    ceB_v.neighbors.push_back(pair<int, int>(4, cpAB)); // Empty B -> Move to pouring A to B, cost = cpAB

    cpAB_v.neighbors.push_back(pair<int, int>(0, cfA)); // Pour A to B -> Move to filling A, cost = cfA
    cpAB_v.neighbors.push_back(pair<int, int>(3, ceB)); // Pour A to B -> Move to emptying B, cost = ceB
    cpAB_v.neighbors.push_back(pair<int, int>(5, cpBA)); // Pour A to B -> Move to pouring B to A, cost = cpBA

    cpBA_v.neighbors.push_back(pair<int, int>(0, cfA)); // Pour B to A -> Move to filling A, cost = cfA
    cpBA_v.neighbors.push_back(pair<int, int>(1, cfB)); // Pour B to A -> Move to filling B, cost = cfB
    cpBA_v.neighbors.push_back(pair<int, int>(2, ceA)); // Pour B to A -> Move to emptying A, cost = ceA
    cpBA_v.neighbors.push_back(pair<int, int>(3, ceB)); // Pour B to A -> Move to emptying B, cost = ceB
    cpBA_v.neighbors.push_back(pair<int, int>(4, cpAB)); // Pour B to A -> Move to pouring A to B, cost = cpAB

    // Add the vertices to the graph
    graph.push_back(cfA_v);  // 0
    graph.push_back(cfB_v);  // 1
    graph.push_back(ceA_v);  // 2
    graph.push_back(ceB_v);  // 3
    graph.push_back(cpAB_v); // 4
    graph.push_back(cpBA_v); // 5
}

// Destructor for the Jug class
Jug::~Jug() {
    graph.clear();
}

// Solve method to find the solution and store it in the provided string
int Jug::solve(string& solution) {
    vector<int> steps;

    // Check if input values are valid
    if (!isValidInputs()) {
        solution = "";
        return -1;
    }

    // Attempt to find a solution
    steps = attempt();

    if (!steps.empty()) {
        // Found a solution
        processString(steps, solution);
        return 1;
    } else {
        // No solution found
        solution = "";
        return 0;
    }
}

// Check if input values are valid
bool Jug::isValidInputs() const {
    return (N >= 0 && cfA >= 0 && cfB >= 0 && ceA >= 0 && ceB >= 0 && cpAB >= 0 && cpBA >= 0)
    && (Ca > 0 && Ca <= Cb) && (N <= Cb && Cb <= 1000);
}

// Check if the amount is correct
bool Jug::isCorrectAmount(list<pair<int, int>> route) {
    return route.back().first /* A */ == 0 && route.back().second /* B */ == N;
}

// Process the input string and update the vector of steps
int Jug::processString(vector<int>& steps, string& solution) const {
    ostringstream outSS;
    int totalCost = 0;

    // Iterate over steps and update the output string
    for (unsigned i = 0; i < steps.size(); ++i) {
        if (steps.at(i) == 0) {
            totalCost += cfA;
            outSS << "fill A" << endl;
        } else if (steps.at(i) == 1) {
            totalCost += cfB;
            outSS << "fill B" << endl;
        } else if (steps.at(i) == 2) {
            totalCost += ceA;
            outSS << "empty A" << endl;
        } else if (steps.at(i) == 3) {
            totalCost += ceB;
            outSS << "empty B" << endl;
        } else if (steps.at(i) == 4) {
            totalCost += cpAB;
            outSS << "pour A B" << endl;
        } else if (steps.at(i) == 5) {
            totalCost += cpBA;
            outSS << "pour B A" << endl;
        }
    }

    // Update the output string with success and total cost
    outSS << "success " << totalCost;
    solution = outSS.str();

     return totalCost;
}

// Process the total cost of a solution
int Jug::processTotalCost(vector<int> steps) {
    int totalCost = 0;

    // Calculate the total cost based on the steps
    for (unsigned i = 0; i < steps.size(); ++i) {
        if (steps.at(i) == 0) {
            totalCost += cfA; // Add the cost of filling A
        } else if (steps.at(i) == 1) {
            totalCost += cfB; // Add the cost of filling B
        } else if (steps.at(i) == 2) {
            totalCost += ceA; // Add the cost of emptying A
        } else if (steps.at(i) == 3) {
            totalCost += ceB; // Add the cost of emptying B
        } else if (steps.at(i) == 4) {
            totalCost += cpAB; // Add the cost of pouring A to B
        } else if (steps.at(i) == 5) {
            totalCost += cpBA; // Add the cost of pouring B to A
        }
    }

    return totalCost;
}

// Attempt to solve the Jug problem
vector<int> Jug::attempt() {
    list<pair<int, int>> aRoute;
    list<pair<int, int>> bRoute;

    vector<int> aSteps;
    vector<int> bSteps;

    aRoute.push_back(pair<int, int>(0, 0));
    bRoute.push_back(pair<int, int>(0, 0));

    aSteps = traverse(0, aSteps, aRoute); // Traverse graph starting from filling A
    bSteps = traverse(1, bSteps, bRoute); // Traverse graph starting from filling B

    // Choose the solution with the lower total cost
    if (aSteps.empty()) {
        return bSteps;
    } else if (bSteps.empty()) {
        return aSteps;
    }
    
    return processTotalCost(aSteps) < processTotalCost(bSteps) ? aSteps : bSteps;
}

// Perform a step in the solution process
int Jug::doStep(int& aAmount, int& bAmount, const int& stepIndex) {
    // Update the amounts based on the selected step
    if (graph.at(stepIndex).key == "cfA") { // If the step is to fill A
        aAmount = Ca; // Fill A to its maximum capacity
    } else if (graph.at(stepIndex).key == "cfB") { // If the step is to fill B
        bAmount = Cb; // Fill B to its maximum capacity
    } else if (graph.at(stepIndex).key == "ceA") { // If the step is to empty A
        aAmount = 0; // Empty A
    } else if (graph.at(stepIndex).key == "ceB")  { // If the step is to empty B
        bAmount = 0; // Empty B
    } else if (graph.at(stepIndex).key == "cpAB") { // If the step is to pour from A to B
        if (aAmount + bAmount <= Cb) { // If pouring won't overflow B
            bAmount += aAmount; // Pour all of A into B
            aAmount = 0; // A becomes empty
        } else { // If pouring will overflow B
            aAmount -= (Cb - bAmount); // Pour only enough from A to fill B
            bAmount = Cb; // B becomes full
        }
    } else if (graph.at(stepIndex).key == "cpBA")  { // If the step is to pour from B to A
        if (aAmount + bAmount <= Ca) { // If pouring won't overflow A
            aAmount += bAmount; // Pour all of B into A
            bAmount = 0; // B becomes empty
        } else { // If pouring will overflow A
            bAmount -= (Ca - aAmount); // Pour only enough from B to fill A
            aAmount = Ca; // A becomes full
        }
    }

    return stepIndex;
}

// Traverse the graph to find a solution
vector<int> Jug::traverse(int stepIndex, vector<int> steps, list<pair<int, int>> route) {
    vector<int> vect;
    vector<int> vectAlt;

    int aAmount;
    int bAmount;
    int stepTaken;

    // Check if the correct amount is reached
    if (isCorrectAmount(route)) {
        return steps;
    }

    // Iterate over neighbors and explore paths
    auto it = graph.at(stepIndex).neighbors.begin();

    while (it != graph.at(stepIndex).neighbors.end()) {
        aAmount = route.back().first;
        bAmount = route.back().second;
        stepTaken = doStep(aAmount, bAmount, it->first);

        // Check for cycles and explore new paths
        if (!checkIfCycled(aAmount, bAmount, route)) {
            steps.push_back(stepTaken);
            route.push_back(pair<int, int>(aAmount, bAmount));

            // Recursively traverse the graph
            if (vect.size() == 0) {
                vect = traverse(stepTaken, steps, route);
            } else {
                vectAlt = traverse(stepTaken, steps, route);
                // Choose the path with the lower total cost
                if (processTotalCost(vect) > processTotalCost(vectAlt)) {
                    vect = vectAlt;
                }
            }

            steps.pop_back();
            route.pop_back();
        }

        it++;
    }

    return vect;
}

// Check if a cycle is encountered in the traversal
bool Jug::checkIfCycled(int aAmount, int bAmount, list<pair<int, int>> route) {
    auto it = route.begin();

    // Check for cycles in the route
    while (it != route.end()) {
        if (it->first == aAmount && it->second == bAmount) {
            return true;
        }

        it++;
    }

    return false;
}
