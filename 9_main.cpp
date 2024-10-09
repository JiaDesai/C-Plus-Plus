#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>
using namespace std;

const int NUMBERS_SIZE = 50000;

int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}

void fillArrays(int arr1[], int arr2[], int arr3[]) {
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

void QPartition(int numbers[], int low, int high) {
    int pivot = numbers[(low + high) / 2];
    int i = low - 1;
    int j = high + 1;
    while (true) {
        do {
            i++;
        } while (numbers[i] < pivot);
        do {
            j--;
        } while (numbers[j] > pivot);
        if (i >= j)
            return;
        std::swap(numbers[i], numbers[j]);
    }
}

void Quicksort_midpoint(int numbers[], int i, int k) {
    if (i < k) {
        int pivotIndex = (i + k) / 2;
        int pivot = numbers[pivotIndex];
        int left = i;
        int right = k;
        while (left <= right) {
            while (numbers[left] < pivot)
                left++;
            while (numbers[right] > pivot)
                right--;
            if (left <= right) {
                std::swap(numbers[left], numbers[right]);
                left++;
                right--;
            }
        }
        Quicksort_midpoint(numbers, i, right);
        Quicksort_midpoint(numbers, left, k);
    }
}

void Quicksort_medianOfThree(int numbers[], int i, int k) {
    if (i < k) {
        int left = i;
        int right = k;
        int mid = (left + right) / 2;
        int temp;
        if (numbers[left] > numbers[mid]) {
            temp = numbers[left];
            numbers[left] = numbers[mid];
            numbers[mid] = temp;
        }
        if (numbers[left] > numbers[right]) {
            temp = numbers[left];
            numbers[left] = numbers[right];
            numbers[right] = temp;
        }
        if (numbers[mid] > numbers[right]) {
            temp = numbers[mid];
            numbers[mid] = numbers[right];
            numbers[right] = temp;
        }
        int pivot = numbers[mid];
        while (left <= right) {
            while (numbers[left] < pivot)
                left++;
            while (numbers[right] > pivot)
                right--;
            if (left <= right) {
                std::swap(numbers[left], numbers[right]);
                left++;
                right--;
            }
        }
        Quicksort_medianOfThree(numbers, i, right);
        Quicksort_medianOfThree(numbers, left, k);
    }
}

void InsertionSort(int numbers[], int numbersSize) {
    int i, j, key;
    for (i = 1; i < numbersSize; i++) {
        key = numbers[i];
        j = i - 1;
        while (j >= 0 && numbers[j] > key) {
            numbers[j + 1] = numbers[j];
            j = j - 1;
        }
        numbers[j + 1] = key;
    }
}

static void BubbleSort(int numbers[], int n) {
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < n - i - 1; ++j) {
      if (numbers[j] > numbers[j + 1]) {
	std::swap(numbers[j], numbers[j + 1]);
      }
    }
  }
}

static void merge(int numbers[], int start, int mid, int end) {
  int start2 = mid + 1;
 
  // If the direct merge is already sorted
  if (numbers[mid] <= numbers[start2]) {
    return;
  }
 
  // Two pointers to maintain start of both sub-arrays to merge
  while (start <= mid && start2 <= end) {
 
    // If element 1 is in right place
    if (numbers[start] <= numbers[start2]) {
      start++;
    } else {
      int value = numbers[start2];
      int index = start2;
 
      // Shift all the elements between element 1
      // element 2, right by 1.
      while (index != start) {
	numbers[index] = numbers[index - 1];
	index--;
      }
      numbers[start] = value;
 
      // Update all the pointers
      start++;
      mid++;
      start2++;
    }
  }
}

static void MergeSort(int numbers[], int left, int right) {
  if (left < right) {
    int mid = (left + right)/2;
    MergeSort(numbers, left, mid);
    MergeSort(numbers, mid+1, right);
    merge(numbers, left, mid, right);
  }
}

static void RadixSort(int numbers[], int size) {
  // LOTS of assumptions here.  I assume all data are
  // postive integers;
  
  // I have to do passes based on the digits.  I stop
  // when I extract the largest digit
  int divisor = 1;
  bool more = true;
  for(int pass=0; more ; pass++) {
    // I need 10 buckets with a lot of room in them
    std::vector< std::vector<int> > buckets(10);
    for(int i=0;i<10;++i) buckets[i].reserve(NUMBERS_SIZE);

    // I pull off the pass'th digit and use it to put a number
    // into a bucket.  To get it, I divide by 1, 10, 100, 1000
    // and then do a modulo
    more = false;
    for(int i=0; i<size; ++i) {
      int digit = (numbers[i]/divisor)%10;
      if (numbers[i]/divisor/10 > 0) more = true;
      buckets[digit].push_back(numbers[i]);
    }
    divisor *= 10;

    // Copy the buckets back into numbers
    int index = 0;
    for(int i=0; i<10; ++i) {
      const std::vector<int>& bucket = buckets[i];
      for(int j=0; j<static_cast<int>(bucket.size()); ++j) {
	numbers[index++] = bucket[j];
      }
    }
  }
}


static bool is_sorted(int numbers[], int numbersSize) {
    if (numbersSize <= 0) return true;
    int last = numbers[0];
    for(int i = 1; i < numbersSize; ++i) {
        if (numbers[i] < last) return false;
        last = numbers[i];
    }
    return true;
}

static void copy_vector_into_array(const vector<int>& source, int array[]) {
    for(size_t i = 0; i < source.size(); ++i) {
        array[i] = source[i];
    }
}


int main() {
    srand(time(NULL));
    vector<int> sample;
    sample.reserve(NUMBERS_SIZE);
    for(int i=0; i<NUMBERS_SIZE; ++i) {
        sample.push_back(rand() % (NUMBERS_SIZE + 1));
    }

    int test_sizes[4] = { 10, 100, 1000, 50000 };
    int test_array[NUMBERS_SIZE];

    for(int i=0; i<4; ++i) {
        int size = test_sizes[i];
        cout << endl;
        cout << "-------------------- size " << size << " --------------------" << endl;

        // Copy sample vector into test_array
        copy_vector_into_array(sample, test_array);

        // Quicksort_midpoint
        {
            cout << "Quicksort_midpoint: ";
            auto start = chrono::high_resolution_clock::now();
            Quicksort_midpoint(test_array, 0, size - 1);
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
            cout << duration << " microseconds." << endl;
        }

        // Quicksort_medianOfThree
        {
            copy_vector_into_array(sample, test_array);
            cout << "Quicksort_medianOfThree: ";
            auto start = chrono::high_resolution_clock::now();
            Quicksort_medianOfThree(test_array, 0, size - 1);
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
            cout << duration << " microseconds." << endl;
        }

        // InsertionSort
        {
            copy_vector_into_array(sample, test_array);
            cout << "InsertionSort: ";
            auto start = chrono::high_resolution_clock::now();
            InsertionSort(test_array, size);
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
            cout << duration << " microseconds." << endl;
        }
    }

    return 0;
}
