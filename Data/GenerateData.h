//
// Created by Adam on 15/03/2025.
//

#ifndef AIZO1_GENERATEDATA_H
#define AIZO1_GENERATEDATA_H

#include <random>
#include <type_traits>
#include "DataArrangement.h"

template<typename T>
class GenerateData {
public:
    static void generateRandom(T arr[], int n, T max) {
        static_assert(std::is_arithmetic<T>::value, "Generates data only with numeric types");

        static std::random_device rd;
        static std::default_random_engine engine(rd());

        if constexpr (std::is_integral<T>::value) {
            std::uniform_int_distribution<T> distribution(0, max);
            for (int i = 0; i < n; ++i) {
                arr[i] = distribution(engine);
            }
        } else if constexpr (std::is_floating_point<T>::value) {
            std::uniform_real_distribution<T> distribution(0, max);
            for (int i = 0; i < n; ++i) {
                arr[i] = distribution(engine);
            }
        }
    }

    static void generateFullySortedAscending(T arr[], int n, T max) {
        static_assert(std::is_arithmetic<T>::value, "Generates data only with numeric types");

        for (int i = 0; i < n; ++i) {
            arr[i] = (static_cast<T>(i) * max) / static_cast<T>(n - 1);
        }
    }

    static void generateFullySortedDescending(T arr[], int n, T max) {
        static_assert(std::is_arithmetic<T>::value, "Generates data only with numeric types");

        for (int i = 0; i < n; ++i) {
            arr[i] = (static_cast<T>(n - 1 - i) * max) / static_cast<T>(n - 1);
        }
    }

    static void generatePartiallySorted33(T arr[], int n, T max) {
        static_assert(std::is_arithmetic<T>::value, "Generates data only with numeric types");
        int boundary = (n * 33) / 100;
        for (int i = 0; i < boundary; ++i) {
            arr[i] = static_cast<T>(0);
        }
        generateRandom(arr + boundary, n - boundary, max);
    }

    static void generatePartiallySorted66(T arr[], int n, T max) {
        static_assert(std::is_arithmetic<T>::value, "Generates data only with numeric types");
        int boundary = (n * 66) / 100;
        for (int i = 0; i < boundary; ++i) {
            arr[i] = static_cast<T>(0);
        }
        generateRandom(arr + boundary, n - boundary, max);
    }

    static void generateData(DataArrangement arrangement, T arr[], int n, T max) {
        switch(arrangement) {
            case DataArrangement::FULLY_SORTED_ASCENDING:
                generateFullySortedAscending(arr, n, max);
                break;
            case DataArrangement::FULLY_SORTED_DESCENDING:
                generateFullySortedDescending(arr, n, max);
                break;
            case DataArrangement::PARTIALLY_SORTED_33:
                generatePartiallySorted33(arr, n, max);
                break;
            case DataArrangement::PARTIALLY_SORTED_66:
                generatePartiallySorted66(arr, n, max);
                break;
            case DataArrangement::RANDOM:
            default:
                generateRandom(arr, n, max);
                break;
        }
    }
};

#endif //AIZO1_GENERATEDATA_H
