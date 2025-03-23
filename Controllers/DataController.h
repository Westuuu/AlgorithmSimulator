//
// Created by Adam on 15/03/2025.
//

#ifndef AIZO1_DATACONTROLLER_H
#define AIZO1_DATACONTROLLER_H

#include "iostream"
#include "../Data/GenerateData.h"
#include "../Data/DataArrangement.h"

template<typename T>

class DataController {
private:
    T *originalData;
    T *testData;
    int arraySize;
    int maxValue;
    DataArrangement dataArrangement;

public:
    DataController(int arraySize, int maxValue) : arraySize(arraySize), maxValue(maxValue) {
        originalData = new T[arraySize];
        testData = new T[arraySize];
    }

    ~DataController() {
        delete[] originalData;
        delete[] testData;
    }

    void generateData(DataArrangement arrangement) {
        setDataArrangement(arrangement);
        GenerateData<T>::generateData(arrangement, originalData, arraySize, maxValue);
        resetTestData();
    }

    void resetTestData() {
        for (int i = 0; i < arraySize; ++i) {
            testData[i] = originalData[i];
        }
    }

    bool checkIfSortedASC(T arr[], int n) {
        for (int i = 1; i < n; ++i) {
            if (arr[i] < arr[i - 1]) {
                return false;
            }
        }
        return true;
    }

    void setDataArrangement(DataArrangement &arrangement) {
        dataArrangement = arrangement;
    }

    T *getTestData() {
        return testData;
    }

    int getArraySize() {
        return arraySize;
    }
};


#endif //AIZO1_DATACONTROLLER_H
