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
    int ITERATIONS;
    DataController<T> &dataManager;
    ResultsController &resultsController;
    std::vector<std::function<void(T *, int)>> algorithms;
    std::vector<std::string> algorithmNames;
    bool PRINTRESULTS = false;

    double measureExecutionTime(std::function<void(T *, int)> algorithm) {
        T *data = dataManager.getTestData();
        int arraySize = dataManager.getArraySize();

        auto start = std::chrono::high_resolution_clock::now();
        algorithm(data, arraySize);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::milli> duration = end - start;
        return duration.count();
    }

    void printArray(T arr[], int size) {
        constexpr int maxDisplayElements = 50;
        int displayCount = std::min(size, maxDisplayElements);

        for (int i = 0; i < displayCount; i++) {
            std::cout << arr[i] << " ";
        }

        if (size > maxDisplayElements) {
            std::cout << "... (" << (size - maxDisplayElements) << " more elements)";
        }
        std::cout << std::endl;
    }

    std::string getArrangementName(DataArrangement arrangement) {
        switch (arrangement) {
            case DataArrangement::RANDOM:
                return "Random";
            case DataArrangement::FULLY_SORTED_ASCENDING:
                return "Ascending";
            case DataArrangement::FULLY_SORTED_DESCENDING:
                return "Descending";
            case DataArrangement::PARTIALLY_SORTED_33:
                return "33% Sorted";
            case DataArrangement::PARTIALLY_SORTED_66:
                return "66% Sorted";
        }
    }

public:
    SimulationController(DataController<T> &dataManager, ResultsController &resultsController, int iterations)
            : dataManager(dataManager), resultsController(resultsController), ITERATIONS(iterations) {}


    void registerAlgorithm(const std::string &name, std::function<void(T *, int)> algorithm) {
        algorithmNames.push_back(name);
        algorithms.push_back(algorithm);
    }

    void runAlgorithm(const std::string &name, std::function<void(T *, int)> testedAlgorithm,
                      DataArrangement dataArrangement, int runNumber) {
        dataManager.resetTestData();


        T *data = dataManager.getTestData();
        int arraySize = dataManager.getArraySize();
        if (PRINTRESULTS) {
            std::cout << "Before sorting with " << name << " (run " << runNumber << ", "
                      << getArrangementName(dataArrangement) << "):" << std::endl;
            printArray(data, arraySize);
        }

        double executionTime = measureExecutionTime(testedAlgorithm);

        bool sortedCorrectly = dataManager.verifyIfSortedCorrectly(data, arraySize);


        if (PRINTRESULTS) {
            std::cout << "After sorting with " << name << " (run " << runNumber << ", "
                      << getArrangementName(dataArrangement) << "):" << std::endl;
            printArray(data, arraySize);
            std::cout << "Sorted correctly: " << (sortedCorrectly ? "Yes" : "No") << std::endl;
            std::cout << "Execution time: " << executionTime << " ms" << std::endl << std::endl;
        }


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
        const std::vector<DataArrangement> dataArrangements = getDataArrangements();
        int k = 0;

        for (auto arrangement: dataArrangements) {
            dataManager.setDataArrangement(arrangement);

            for (int i = 0; i < ITERATIONS; ++i) {
                k++;
                cout << "Running simulation iteration " << k << "/" << ITERATIONS * dataArrangements.size() << endl;

                dataManager.generateData(arrangement);

                for (int j = 0; j < algorithms.size(); ++j) {
                    runAlgorithm(algorithmNames[j], algorithms[j], arrangement, i + 1);
                }
            }
        }
        resultsController.saveResultsByAlgorithm("results");
    }

    void setPrintResultFlag(bool flag) {
        PRINTRESULTS = flag;
    }
};


#endif //AIZO1_SIMULATIONCONTROLLER_H
