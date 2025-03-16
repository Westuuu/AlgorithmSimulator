//
// Created by Adam on 16/03/2025.
//

#ifndef AIZO1_ALGORITHMMANAGER_H
#define AIZO1_ALGORITHMMANAGER_H


#include "../Data/SortingDataManager.h"
#include "../Data/DataArrangement.h"
#include "map"

template<typename T>

class AlgorithmManager {
private:
    SortingDataManager<T> &dataManager;

    std::map<std::string, double> timingResults;

    double measureExecutionTime(std::function<void(T *, int)> algorithm) {
        T *data = dataManager.getTestData();
        int arraySize = dataManager.getArraySize();

        auto start = std::chrono::high_resolution_clock::now();
        algorithm(data, arraySize);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> duration = start - end;
        return duration.count();
    }

public:
    AlgorithmManager(SortingDataManager<T> &dataManager) : dataManager(dataManager) {}

    void runAlgorithm(const std::string &name, std::function<void(T *, int)> testedAlgorithm) {
        dataManager.resetTestData();

        double executionTime = measureExecutionTime(testedAlgorithm);
        timingResults[name] = executionTime;
    }
};


#endif //AIZO1_ALGORITHMMANAGER_H
