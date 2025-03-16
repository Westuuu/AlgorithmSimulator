//
// Created by Adam on 16/03/2025.
//

#ifndef AIZO1_ALGORITHMCONTROLLER_H
#define AIZO1_ALGORITHMCONTROLLER_H


#include "SortingDataController.h"
#include "../Data/DataArrangement.h"
#include "map"
#include "ResultsController.h"

template<typename T>

class AlgorithmController {
private:
    SortingDataController<T> &dataManager;
    ResultsController &resultsManager;
    std::map<std::string, double> timingResults;

    double measureExecutionTime(std::function<void(T *, int)> algorithm) {
        T *data = dataManager.getTestData();
        int arraySize = dataManager.getArraySize();

        auto start = std::chrono::high_resolution_clock::now();
        algorithm(data, arraySize);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> duration = end - start;
        return duration.count();
    }

public:
    AlgorithmController(SortingDataController<T> &dataManager, ResultsController &resultsManager)
            : dataManager(dataManager), resultsManager(resultsManager) {}

    void runAlgorithm(const std::string &name, std::function<void(T *, int)> testedAlgorithm,
                      DataArrangement dataArrangement, int runNumber) {
        dataManager.resetTestData();

        double executionTime = measureExecutionTime(testedAlgorithm);
        timingResults[name] = executionTime;

        T *data = dataManager.getTestData();
        int arraySize = dataManager.getArraySize();
        bool sortedCorrectly = dataManager.checkIfSortedASC(data, arraySize);

        SortingResult result;
        result.algorithmName = name;
        result.arrangement = dataArrangement;
        result.runNumber = runNumber;
        result.executionTimeMs = executionTime;
        result.sortedCorrectly = sortedCorrectly;

        resultsManager.addResult(result);
    }
};


#endif //AIZO1_ALGORITHMCONTROLLER_H
