//
// Created by Adam on 16/03/2025.
//

#include "ResultsController.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include "filesystem"
#include <algorithm>

void ResultsController::addResult(const SortingResult &result) {
    results.push_back(result);
}

void ResultsController::saveResultsToCSV(const std::string &filename) const {
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


void ResultsController::saveResultsByAlgorithm(const std::string &directory) const {
    try {
        std::filesystem::create_directory(directory);
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "Error creating directory: " << e.what() << std::endl;
    }

    std::map<std::string, std::vector<SortingResult> > resultsByAlgorithm;

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


void ResultsController::printResults() const {
    std::cout << std::left
            << std::setw(25) << "Algorithm"
            << std::setw(25) << "Arrangement"
            << std::setw(15) << "Run"
            << std::setw(20) << "Time (ms)"
            << std::setw(25) << "Sorted"
            << std::setw(15) << "Data Type"
            << std::setw(15) << "Array Size" << std::endl;
    std::cout << std::string(150, '-') << std::endl;

    for (const auto &result: results) {
        std::cout << std::left
                << std::setw(35) << result.algorithmName
                << std::setw(25) << arrangementToString(result.arrangement)
                << std::setw(15) << result.runNumber
                << std::setw(20) << std::fixed << std::setprecision(4) << result.executionTimeMs
                << std::setw(25) << (result.sortedCorrectly ? "Yes" : "No")
                << std::setw(15) << result.dataType
                << std::setw(15) << result.ArraySize << std::endl;
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
        default:
            return "Unknown arrangement";
    }
}

void ResultsController::printStatisticsByAlgorithmAndArrangement() const {
    // Group results by algorithm name and arrangement
    std::map<std::pair<std::string, DataArrangement>, std::vector<SortingResult> > groupedResults;

    for (const auto &result: results) {
        groupedResults[{result.algorithmName, result.arrangement}].push_back(result);
    }

    std::cout << "\n=== STATISTICS BY ALGORITHM AND ARRANGEMENT ===\n" << std::endl;
    std::cout << std::left
            << std::setw(30) << "Algorithm"
            << std::setw(30) << "Arrangement"
            << std::setw(15) << "Array Size"
            << std::setw(15) << "Mean (ms)"
            << std::setw(15) << "Median (ms)"
            << std::setw(20) << "Std Deviation (ms)"
            << std::endl;
    std::cout << std::string(150, '-') << std::endl;

    for (const auto &[key, resultList]: groupedResults) {
        const auto &[algorithm, arrangement] = key;

        std::map<int, std::vector<double> > timesBySize;
        for (const auto &result: resultList) {
            timesBySize[result.ArraySize].push_back(result.executionTimeMs);
        }

        for (const auto &[size, times]: timesBySize) {
            double mean = calculateMean(times);
            double median = calculateMedian(times);
            double stdDev = calculateStdDev(times, mean);

            std::cout << std::left
                    << std::setw(30) << algorithm
                    << std::setw(30) << arrangementToString(arrangement)
                    << std::setw(15) << size
                    << std::setw(15) << std::fixed << std::setprecision(4) << mean
                    << std::setw(15) << std::fixed << std::setprecision(4) << median
                    << std::setw(20) << std::fixed << std::setprecision(4) << stdDev
                    << std::endl;
        }
    }
}

double ResultsController::calculateMean(const std::vector<double> &times) {
    if (times.empty()) return 0.0;

    double sum = 0.0;
    for (double time: times) {
        sum += time;
    }
    return sum / times.size();
}

double ResultsController::calculateMedian(std::vector<double> times) {
    if (times.empty()) return 0.0;

    std::sort(times.begin(), times.end());

    size_t size = times.size();
    if (size % 2 == 0) {
        return (times[size / 2 - 1] + times[size / 2]) / 2.0;
    } else {
        return times[size / 2];
    }
}

double ResultsController::calculateStdDev(const std::vector<double> &times, double mean) {
    if (times.size() <= 1) return 0.0;

    double sumSquaredDiffs = 0.0;
    for (double time: times) {
        double diff = time - mean;
        sumSquaredDiffs += diff * diff;
    }

    return std::sqrt(sumSquaredDiffs / (times.size() - 1));
}
