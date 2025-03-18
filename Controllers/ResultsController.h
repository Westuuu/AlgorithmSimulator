//
// Created by Adam on 16/03/2025.
//

#ifndef AIZO1_RESULTSCONTROLLER_H
#define AIZO1_RESULTSCONTROLLER_H

#include <vector>
#include "../Data/DataArrangement.h"

struct SortingResult {
    std::string algorithmName;
    DataArrangement arrangement;
    int runNumber;
    double executionTimeMs;
    bool sortedCorrectly;
    std::string dataType;
};

class ResultsController {
private:
    std::vector<SortingResult> results;

public:
    void addResult(const SortingResult &result);

    void saveResultsToCSV(const std::string &filename);

    void saveResultsByAlgorithm(const std::string &directory);

    void printResults();

    static std::string arrangementToString(const DataArrangement &arrangement);
};

#endif //AIZO1_RESULTSCONTROLLER_H
