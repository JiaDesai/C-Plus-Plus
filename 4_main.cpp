#include "Jug.h"    
#include <iostream>

using namespace std;

int main()
{
    string solution;

    // Create an instance of the Jug class with specified parameters
    Jug head(3, 5, 4, 1, 2, 3, 4, 5, 6);

    // Call the solve method on the Jug object and check for errors
    if (head.solve(solution) != 1)
    {
        // Display an error message if solve method returns an error code
        cout << "Error 3" << endl;
    }

    cout << solution << endl << endl;

    string solution2;

    // Create a second instance of the Jug class with different parameters
    Jug head2(3, 5, 4, 1, 1, 1, 1, 1, 2);

    // Call the solve method on the second Jug object and check for errors
    if (head2.solve(solution2) != 1)
    {
        // Display an error message if solve method returns an error code
        cout << "Error 3" << endl;
    }

    cout << solution2 << endl;

    return 0;
}
