#include <iostream>
#include "SortingAlgorithms/InsertionSort.h"
#include "SortingAlgorithms/HeapSort.h"
#include "Data/GenerateData.h"
#include "Data/ValidateIfSorted.h"
#include "SortingAlgorithms/ShellSort.h"

using namespace std;

int main() {
    int ARRAY_SIZE = 5000000;
    int MAX_SIZE = ARRAY_SIZE;
    auto *arr = new int[ARRAY_SIZE];
    GenerateData<int>::generateRandom(arr, ARRAY_SIZE, MAX_SIZE);

    auto *darr = new double[ARRAY_SIZE];
    GenerateData<double>::generateRandom(darr, ARRAY_SIZE, MAX_SIZE);


    HeapSort<int>::sort(arr, ARRAY_SIZE);
    bool isHeapSorted = ValidateIfSorted<int>::checkIfSortedASC(arr, ARRAY_SIZE);
    if (isHeapSorted) {
        cout << "Heap sort finished" << endl;
    } else {
        cout << "Data is not sorted, used sorting method: HeapSort" << endl;
    }

    cout << endl;

//    InsertionSort<double>::sort(darr, ARRAY_SIZE);
    bool isInsertionSorted = ValidateIfSorted<double>::checkIfSortedASC(darr, ARRAY_SIZE);
    if (isInsertionSorted) {
        cout << "Insertion sort finished" << endl;
    } else {
        cout << "Data is not sorted, used sorting method: InsertionSort" << endl;
    }

    cout << endl;

    ShellSort<int>::sort(data, ARRAY_SIZE);
    bool isShellSorted = ValidateIfSorted<int>::checkIfSortedASC(data, ARRAY_SIZE);
    if (isShellSorted) {
        cout << "Shell sort finished" << endl;
    } else {
        cout << "Data is not sorted, used sorting method: Shell" << endl;
    }


    delete[] arr;
    delete[] darr;

    return 0;
}
