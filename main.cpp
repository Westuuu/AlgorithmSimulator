#include <iostream>
#include "SortingAlgorithms/InsertionSort.h"

using namespace std;

int main() {
    int arr[] = {0, 0, 5, 4, 3, 2, 1, 3};
    float farr[] = {5.0, 4.02, 3.01, 3.02, 2.1, 1.6};

    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t fn = sizeof(farr) / sizeof(farr[0]);

    for (int i = 0; i < n; ++i) {
        cout << arr[i] << endl;
    }
    cout << "Sorted:" << endl;
    InsertionSort<int>::sort(arr, n);
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << endl;
    }

    cout << endl;

    for (int i = 0; i < fn; ++i) {
        cout << farr[i] << endl;
    }
    cout << "Sorted:" << endl;
    InsertionSort<float>::sort(farr, fn);
    for (int i = 0; i < fn; ++i) {
        cout << farr[i] << endl;
    }


    return 0;
}
