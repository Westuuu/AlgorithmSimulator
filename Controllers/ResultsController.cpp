//
// Created by Adam on 16/03/2025.
//

#include "ResultsController.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include "filesystem"

void ResultsController::addResult(const SortingResult &result) {
    results.push_back(result);
}

void ResultsController::saveResultsToCSV(const std::string &filename) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    file << "Algorithm,Arrangement,RunNumber,ExecutionTime(ms),SortedCorrectly,DataType,ArraySize" << std::endl;

    for (const auto &result: results) {
        file << result.algorithmName << ","
             << arrangementToString(result.arrangement) << ","
             << result.runNumber << ","
             << std::fixed << std::setprecision(4) << result.executionTimeMs << ","
             << (result.sortedCorrectly ? "true" : "false") << ","
             << result.dataType << ","
             << result.ArraySize << std::endl;
    }

    file.close();
    std::cout << "Results saved to " << filename << std::endl;
}


void ResultsController::saveResultsByAlgorithm(const std::string &directory) {
    try {
        std::filesystem::create_directory(directory);
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "Error creating directory: " << e.what() << std::endl;
    }

    std::map<std::string, std::vector<SortingResult>> resultsByAlgorithm;

    for (const auto &result: results) {
        resultsByAlgorithm[result.algorithmName].push_back(result);
    }

    for (const auto &pair: resultsByAlgorithm) {
        const std::string &algorithmName = pair.first;
        const std::vector<SortingResult> &algorithmResults = pair.second;

        std::string filename = directory;
        filename += "/";
        filename += algorithmName;
        filename += ".csv";

        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename << std::endl;
            continue;
        }

        file << "Algorithm,Arrangement,Run,Time(ms),Sorted Correctly,DataType,ArraySize\n";

        for (const auto &result: algorithmResults) {
            file << result.algorithmName << ","
                 << arrangementToString(result.arrangement) << ","
                 << result.runNumber << ","
                 << result.executionTimeMs << ","
                 << (result.sortedCorrectly ? "Yes" : "No") << ","
                 << result.dataType << ","
                 << result.ArraySize << "\n";
        }

        file.close();
    }
}

void ResultsController::printResults() {
    std::cout << std::left
              << std::setw(25) << "Algorithm"
              << std::setw(25) << "Arrangement"
              << std::setw(15) << "Run"
              << std::setw(20) << "Time (ms)"
              << std::setw(25) << "Sorted"
              << std::setw(15) << "Data Type"
              << "Array Size" << std::endl;
    std::cout << std::string(130, '-') << std::endl;

    for (const auto &result: results) {
        std::cout << std::left
                  << std::setw(35) << result.algorithmName
                  << std::setw(25) << arrangementToString(result.arrangement)
                  << std::setw(15) << result.runNumber
                  << std::setw(20) << std::fixed << std::setprecision(8) << result.executionTimeMs
                  << std::setw(25) << (result.sortedCorrectly ? "Yes" : "No")
                  << std::setw(15) << result.dataType
                  << result.ArraySize << std::endl;
    }
}

std::string ResultsController::arrangementToString(const DataArrangement &arrangement) {
    switch (arrangement) {
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