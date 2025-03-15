//
// Created by Adam on 15/03/2025.
//

#ifndef AIZO1_SORTINGDATAMANAGER_H
#define AIZO1_SORTINGDATAMANAGER_H

#include "iostream"
#include "GenerateData.h"

template<typename T>

class SortingDataManager {
private:
    T *originalData;
    T *testData;
    int arraySize;
    int maxValue;

public:
    SortingDataManager(int arraySize, int maxValue) : arraySize(arraySize), maxValue(maxValue) {
        originalData = new T[arraySize];
        testData = new T[arraySize];
    }

    ~SortingDataManager() {
        delete[] originalData;
        delete[] testData;
    }

    void generateRandomData() {
        GenerateData<T>::generateRandom(originalData, arraySize, maxValue);
        std::cout << "Random data generated" << std::endl;
    }
};


#endif //AIZO1_SORTINGDATAMANAGER_H
