//
// Created by Adam on 16/03/2025.
//

#ifndef AIZO1_RESULTSMANAGER_H
#define AIZO1_RESULTSMANAGER_H

#include <vector>
#include "DataArrangement.h"

struct SortingResult {
    std::string algorithmName;
    DataArrangement arrangement;
    int runNumber;
    double executionTimeMs;
    bool sortedCorrectly;
};

class ResultsManager {
private:
    std::vector<SortingResult> results;

public:
    void addResult(const SortingResult& result);
    void saveResultsToCSV(const std::string& filename);
    static std::string arrangementToString(const DataArrangement& arrangement);
};

#endif //AIZO1_RESULTSMANAGER_H
