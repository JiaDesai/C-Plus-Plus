#include "Heap.h"
#include <iostream>

using namespace std;

Heap::Heap() {
    numItems = 0;
}

void Heap::enqueue(PrintJob* job) {
    // Check if the heap is already full
    if (numItems >= MAX_HEAP_SIZE) {
        cout << "Heap is full. Unable to enqueue." << endl;
        return;
    }

    int currentIndex = numItems;
    arr[currentIndex] = job;
    numItems++;

    // Trickle up to maintain heap property
    while (currentIndex > 0 && arr[currentIndex]->getPriority() > arr[(currentIndex - 1) / 2]->getPriority()) {
        swap(arr[currentIndex], arr[(currentIndex - 1) / 2]);
        currentIndex = (currentIndex - 1) / 2;
    }
}

void Heap::dequeue() {
    // Check if the heap is empty
    if (numItems == 0) {
        cout << "Heap is empty. Unable to dequeue." << endl;
        return;
    }

    // Replace the root with the last element
    arr[0] = arr[numItems - 1];
    numItems--;

    // Trickle down to maintain heap property
    trickleDown(0);
}

void Heap::trickleDown(int index) {
    int leftChildIndex = 2 * index + 1;
    int rightChildIndex = 2 * index + 2;
    int maxIndex = index;

    // Find the index of the maximum priority child
    if (leftChildIndex < numItems && arr[leftChildIndex]->getPriority() > arr[maxIndex]->getPriority()) {
        maxIndex = leftChildIndex;
    }
    if (rightChildIndex < numItems && arr[rightChildIndex]->getPriority() > arr[maxIndex]->getPriority()) {
        maxIndex = rightChildIndex;
    }

    // Swap with the maximum priority child and continue trickling down if necessary
    if (maxIndex != index) {
        swap(arr[index], arr[maxIndex]);
        trickleDown(maxIndex);
    }
}

PrintJob* Heap::highest() {
    // Check if the heap is empty
    if (numItems == 0) {
        cout << "Heap is empty. No highest priority job." << endl;
        return nullptr;
    }
    return arr[0];
}

void Heap::print() {
    // Check if the heap is empty
    if (numItems == 0) {
        cout << "Heap is empty. Nothing to print." << endl;
        return;
    }

    // Print the highest priority job
    PrintJob* highestJob = highest();
    cout << "Priority: " << highestJob->getPriority() << ", Job Number: " << highestJob->getJobNumber() << ", Number of Pages: " << highestJob->getPages() << endl;
}
