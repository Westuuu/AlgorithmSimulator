//
// Created by Adam on 16/03/2025.
//

#include "ResultsManager.h"
#include <fstream>
#include <iostream>
#include <iomanip>

void ResultsManager::addResult(const SortingResult &result) {
    results.push_back(result);
}

void ResultsManager::saveResultsToCSV(const std::string &filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    // Write CSV header
    file << "Algorithm,Arrangement,RunNumber,ExecutionTime(ms),SortedCorrectly" << std::endl;

    // Write all results
    for (const auto& result : results) {
        file << result.algorithmName << ","
             << arrangementToString(result.arrangement) << ","
             << result.runNumber << ","
             << std::fixed << std::setprecision(8) << result.executionTimeMs << ","
             << (result.sortedCorrectly ? "true" : "false") << std::endl;
    }

    file.close();
    std::cout << "Results saved to " << filename << std::endl;
}


std::string ResultsManager::arrangementToString(const DataArrangement& arrangement) {
    switch(arrangement) {
        case DataArrangement::FULLY_SORTED_ASCENDING:
            return "Sorted ascending";
        case DataArrangement::FULLY_SORTED_DESCENDING:
            return "Sorted descending";
        case DataArrangement::PARTIALLY_SORTED_33:
            return "First 33% sorted";
        case DataArrangement::PARTIALLY_SORTED_66:
            return "First 66% sorted";
        case DataArrangement::RANDOM:
            return "Random";
    }
}