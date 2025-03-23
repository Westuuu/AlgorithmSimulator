//
// Created by Adam on 16/03/2025.
//

#ifndef AIZO1_SIMULATIONCONTROLLER_H
#define AIZO1_SIMULATIONCONTROLLER_H


#include <string>
#include <map>
#include "ResultsController.h"
#include "DataController.h"


template<typename T>
class SimulationController {
private:
    int ITERATIONS = 2;
    DataController<T> &dataManager;
    ResultsController &resultsController;
    std::vector<std::function<void(T *, int)>> algorithms;
    std::vector<std::string> algorithmNames;

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
    SimulationController(DataController<T> &dataManager, ResultsController &resultsController)
            : dataManager(dataManager), resultsController(resultsController) {}


    void registerAlgorithm(const std::string &name, std::function<void(T *, int)> algorithm) {
        algorithmNames.push_back(name);
        algorithms.push_back(algorithm);
    }

    void runAlgorithm(const std::string &name, std::function<void(T *, int)> testedAlgorithm,
                      DataArrangement dataArrangement, int runNumber) {
        dataManager.resetTestData();

        double executionTime = measureExecutionTime(testedAlgorithm);

        T *data = dataManager.getTestData();
        int arraySize = dataManager.getArraySize();
        bool sortedCorrectly = dataManager.checkIfSortedASC(data, arraySize);

        SortingResult result;
        result.algorithmName = name;
        result.arrangement = dataArrangement;
        result.runNumber = runNumber;
        result.executionTimeMs = executionTime;
        result.sortedCorrectly = sortedCorrectly;
        result.dataType = typeid(T).name();
        result.ArraySize = dataManager.getArraySize();

        resultsController.addResult(result);
    }

    void runSimulation() {
        std::vector<DataArrangement> dataArrangements = getDataArrangements();

        for (auto arrangement: dataArrangements) {
            dataManager.setDataArrangement(arrangement);

            for (int i = 0; i < ITERATIONS; ++i) {
                dataManager.generateData(arrangement);

                for (int j = 0; j < algorithms.size(); ++j) {
                    runAlgorithm(algorithmNames[j], algorithms[j], arrangement, i + 1);
                }
            }
        }
    }
};


#endif //AIZO1_SIMULATIONCONTROLLER_H
