//
// Created by Adam on 16/03/2025.
//

#ifndef AIZO1_RESULTSCONTROLLER_H
#define AIZO1_RESULTSCONTROLLER_H

#include <vector>
#include "../Data/DataArrangement.h"
#include <map>

struct SortingResult {
    std::string algorithmName;
    DataArrangement arrangement;
    int runNumber;
    double executionTimeMs;
    bool sortedCorrectly;
    std::string dataType;
    int ArraySize;
    size_t memoryUsageBytes;
};

class ResultsController {
private:
    std::vector<SortingResult> results;

    static double calculateMean(const std::vector<double>& times);
    static double calculateMedian(std::vector<double> times);
    static double calculateStdDev(const std::vector<double>& times, double mean);

public:
    void addResult(const SortingResult &result);

    void saveResultsToCSV(const std::string &filename) const;

    void saveResultsByAlgorithm(const std::string &directory) const;

    void printResults() const;

    static std::string arrangementToString(const DataArrangement &arrangement);

    void printStatisticsByAlgorithmAndArrangement() const;
};

#endif //AIZO1_RESULTSCONTROLLER_H
