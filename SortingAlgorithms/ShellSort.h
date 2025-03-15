//
// Created by Adam on 15/03/2025.
//

#ifndef AIZO1_SHELLSORT_H
#define AIZO1_SHELLSORT_H


template<typename T>
class ShellSort {
public:
    static void sort(T arr[], int n) {
        for (int gap = n/2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; i++) {
                T temp = arr[i];

                int j;
                for (j = i; j >= gap && arr[j - gap] > temp; j-= gap) {
                    arr[j] = arr[j - gap];
                }

                arr[j] = temp;
            }
        }
    }

};



#endif //AIZO1_SHELLSORT_H
