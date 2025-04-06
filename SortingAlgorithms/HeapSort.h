//
// Created by Adam on 14/03/2025.
//

#ifndef AIZO1_HEAPSORT_H
#define AIZO1_HEAPSORT_H
using namespace std;



template<typename T>
class HeapSort {
public:
    static void sort(T arr[], int n) {
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }

        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);

            heapify(arr, i, 0);
        }
    }

private:
    static void heapify(T arr[], int n, int i) {
        int largest = i;

        int leftIndex = 2 * i + 1;

        int rightIndex = 2 * i + 2;

        if (leftIndex < n && arr[leftIndex] > arr[largest]) {
            largest = leftIndex;
        }

        if (rightIndex < n && arr[rightIndex] > arr[largest]) {
            largest = rightIndex;
        }

        if (largest != i) {
            swap(arr[i], arr[largest]);

            heapify(arr, n, largest);
        }
    }
};


#endif //AIZO1_HEAPSORT_H
