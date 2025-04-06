//
// Created by Adam on 15/03/2025.
//

#ifndef AIZO1_DATACONTROLLER_H
#define AIZO1_DATACONTROLLER_H

#include "iostream"
#include "../Data/GenerateData.h"
#include "../Data/DataArrangement.h"
#include "map"
#include <fstream>
#include <sstream>
#include <string>

template<typename T>
class DataController {
private:
    T *originalData;
    T *testData;
    int arraySize;
    int maxValue;
    DataArrangement dataArrangement;

    bool checkIfSortedASC(T arr[], int n) {
        for (int i = 1; i < n; ++i) {
            if (arr[i] < arr[i - 1]) {
                return false;
            }
        }
        return true;
    }

public:
    DataController(int arraySize, int maxValue) : arraySize(arraySize), maxValue(maxValue), dataArrangement() {
        originalData = new T[arraySize];
        testData = new T[arraySize];
    }

    ~DataController() {
        delete[] originalData;
        delete[] testData;
    }

    void generateData(DataArrangement arrangement) {
        GenerateData<T>::generateData(arrangement, originalData, arraySize, maxValue);
        resetTestData();
    }

    bool loadDataFromCSV(const std::string &filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << " for reading." << std::endl;
            return false;
        }

        std::string line;
        int index = 0;

        if (std::getline(file, line)) {
            bool isHeader = false;
            for (char c: line) {
                if (!std::isdigit(c) && c != '.' && c != ',' && c != '-' && c != ' ' && c != '\t') {
                    isHeader = true;
                    break;
                }
            }

            if (!isHeader) {
                try {
                    std::stringstream ss(line);
                    std::string value;

                    if (std::getline(ss, value, ',')) {
                        if constexpr (std::is_same_v<T, int>) {
                            originalData[index++] = std::stoi(value);
                        } else if constexpr (std::is_same_v<T, double>) {
                            originalData[index++] = std::stod(value);
                        } else if constexpr (std::is_same_v<T, float>) {
                            originalData[index++] = std::stof(value);
                        }
                    }
                } catch (...) {}
            }
        }
        while (std::getline(file, line) && index < arraySize) {
            std::stringstream ss(line);
            std::string value;

            if (std::getline(ss, value, ',')) {
                if constexpr (std::is_same_v<T, int>) {
                    originalData[index++] = std::stoi(value);
                } else if constexpr (std::is_same_v<T, double>) {
                    originalData[index++] = std::stod(value);
                } else if constexpr (std::is_same_v<T, float>) {
                    originalData[index++] = std::stof(value);
                }
            }
        }

        file.close();
        if (index < arraySize) {
            std::cerr << "Warning: Only read " << index << " elements from CSV, but array size is " << arraySize <<
                    std::endl;
            arraySize = index;
        }

        resetTestData();

        return true;
    }

    void resetTestData() {
        for (int i = 0; i < arraySize; ++i) {
            testData[i] = originalData[i];
        }
    }

    bool verifyIfSortedCorrectly(T arr[], int n) {
        if (!checkIfSortedASC(arr, n)) {
            return false;
        }

        std::map<T, int> originalDataFrequency;
        std::map<T, int> testDataFrequency;

        for (int i = 0; i < n; ++i) {
            ++originalDataFrequency[originalData[i]];
        }
        for (int i = 0; i < n; ++i) {
            ++testDataFrequency[testData[i]];
        }

        if (originalDataFrequency.size() != testDataFrequency.size()) {
            return false;
        }

        for (const auto &pair: originalDataFrequency) {
            auto element = testDataFrequency.find(pair.first);
            if (element == testDataFrequency.end() || element->second != pair.second) {
                return false;
            }
        }
        return true;
    }


    void setDataArrangement(DataArrangement &arrangement) {
        dataArrangement = arrangement;
    }

    T *getTestData() {
        return testData;
    }

    int getArraySize() {
        return arraySize;
    }
};


#endif //AIZO1_DATACONTROLLER_H
