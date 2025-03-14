//
// Created by Adam on 14/03/2025.
//

#ifndef AIZO1_INSERTIONSORT_H
#define AIZO1_INSERTIONSORT_H


#include <cstddef>

template<typename T>
class InsertionSort {
public:
    static void sort(T arr[], int n) {
        for (int i = 1; i < n; ++i) {
            T key = arr[i];
            int j = i - 1;

            while (j >= 0 && key < arr[j]) {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = key;
        }
    }
};


#endif //AIZO1_INSERTIONSORT_H
