//
// Created by Adam on 19/03/2025.
//

#ifndef AIZO1_QUICKSORT_H
#define AIZO1_QUICKSORT_H

#include "../Data/PivotStrategy.h"
#include "random"

template<typename T>
class Quicksort {
private:
    static std::mt19937 &getRandomEngine() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }

    static int choosePivot(int leftIndex, int rightIndex, PivotStrategy pivotStrategy) {
        switch (pivotStrategy) {
            case PivotStrategy::LEFT:
                return leftIndex;
            case PivotStrategy::RIGHT:
                return rightIndex;
            case PivotStrategy::MIDDLE:
                return leftIndex + (rightIndex - leftIndex) / 2;
            case PivotStrategy::RANDOM: {
                std::uniform_int_distribution<> dist(leftIndex, rightIndex);
                return dist(getRandomEngine());
            }
            default:
                return leftIndex + (rightIndex - leftIndex) / 2;
        }
    }

    static int partition(T arr[], int leftIndex, int rightIndex, PivotStrategy pivotStrategy) {
        int pivotIndex = choosePivot(leftIndex, rightIndex, pivotStrategy);
        T pivotValue = arr[pivotIndex];

        std::swap(arr[pivotIndex], arr[rightIndex]);

        int i = leftIndex;

        for (int j = leftIndex; j < rightIndex; j++) {
            if (arr[j] < pivotValue) {
                std::swap(arr[j], arr[i]);
                i++;
            }
        }

        std::swap(arr[i], arr[rightIndex]);
        return i;
    }

    static void sortHelper(T arr[], int leftIndex, int rightIndex, PivotStrategy pivotStrategy) {
        if (leftIndex < rightIndex) {
            int pivotPosition = partition(arr, leftIndex, rightIndex, pivotStrategy);
            sortHelper(arr, leftIndex, pivotPosition - 1, pivotStrategy);
            sortHelper(arr, pivotPosition + 1, rightIndex, pivotStrategy);
        }
    }

public:
    static void sort(T arr[], const int n, const PivotStrategy pivotStrategy) {
        sortHelper(arr, 0, n - 1, pivotStrategy);
    }
};


#endif //AIZO1_QUICKSORT_H
