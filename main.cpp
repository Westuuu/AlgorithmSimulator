#include <iostream>
#include "SortingAlgorithms/InsertionSort.h"
#include "SortingAlgorithms/HeapSort.h"
#include "Data/GenerateData.h"

using namespace std;

int main() {
    int ARRAY_SIZE = 70000;
    int MAX_SIZE = 50000;
    auto *arr = new int[ARRAY_SIZE];
    GenerateData<int>::generateRandom(arr, ARRAY_SIZE, MAX_SIZE);

    auto *darr = new double[ARRAY_SIZE];
    GenerateData<double>::generateRandom(darr, ARRAY_SIZE, MAX_SIZE);


    HeapSort<int>::sort(arr, ARRAY_SIZE);
    cout << "Heapsort finished" << endl;

    cout << endl;

    InsertionSort<double>::sort(darr, ARRAY_SIZE);
    cout << "Insertion sort finished" << endl;


    delete[] arr;
    delete[] darr;

    return 0;
}
