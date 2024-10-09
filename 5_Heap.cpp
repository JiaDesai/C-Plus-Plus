#include <iostream>
#include "Heap.h"

using namespace std;

int main() {
    // Create a heap object
    Heap heap;

    // Create some print jobs
    PrintJob job1(3, 101, 5);
    PrintJob job2(2, 102, 10);
    PrintJob job3(5, 103, 8);
    PrintJob job4(4, 104, 6);

    // Enqueue the print jobs
    heap.enqueue(&job1);
    heap.enqueue(&job2);
    heap.enqueue(&job3);
    heap.enqueue(&job4);

    // Print the highest priority job
    cout << "Highest priority job: ";
    heap.print();

    // Dequeue the highest priority job
    cout << "Dequeueing the highest priority job..." << endl;
    heap.dequeue();

    // Print the new highest priority job
    cout << "Highest priority job after dequeue: ";
    heap.print();

    return 0;
}
