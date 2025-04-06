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
private:
    static std::mt19937 &getRandomEngine() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }
public:
    static void generateRandom(T arr[], int n, T max) {
        static_assert(std::is_arithmetic_v<T>, "Generates data only with numeric types");

        static std::random_device rd;
        static std::default_random_engine engine(rd());

        if constexpr (std::is_integral_v<T>) {
            std::uniform_int_distribution<T> distribution(0, max);
            for (int i = 0; i < n; ++i) {
                arr[i] = distribution(engine);
            }
        } else if constexpr (std::is_floating_point_v<T>) {
            std::uniform_real_distribution<T> distribution(0, max);
            for (int i = 0; i < n; ++i) {
                arr[i] = distribution(engine);
            }
        }
    }

    static void generateFullySortedAscending(T arr[], int n, T max) {
        static_assert(std::is_arithmetic_v<T>, "Generates data only with numeric types");

        for (int i = 0; i < n; ++i) {
            arr[i] = static_cast<T>(static_cast<double>(i) * static_cast<double>(max) / static_cast<double>(n - 1));
        }
    }

    static void generateFullySortedDescending(T arr[], int n, T max) {
        static_assert(std::is_arithmetic_v<T>, "Generates data only with numeric types");

        for (int i = 0; i < n; ++i) {
            arr[i] = max - static_cast<T>(static_cast<double>(i) * static_cast<double>(max) / static_cast<double>(n - 1));
        }
    }

    static void generatePartiallySorted33(T arr[], int n, T max) {
        static_assert(std::is_arithmetic_v<T>, "Generates data only with numeric types");
        int boundary = (n * 33) / 100;
        T maxLowerRange = static_cast<T>((max * 33) / 100);

        if constexpr (std::is_integral_v<T>) {
            std::uniform_int_distribution<T> dist(0, maxLowerRange);
            for (int i = 0; i < boundary; ++i) {
                arr[i] = dist(getRandomEngine());
            }
        } else if constexpr (std::is_floating_point_v<T>) {
            std::uniform_real_distribution<T> dist(0, maxLowerRange);
            for (int i = 0; i < boundary; ++i) {
                arr[i] = dist(getRandomEngine());
            }
        }

        std::sort(arr, arr + boundary);

        if constexpr (std::is_integral_v<T>) {
            std::uniform_int_distribution<T> dist(maxLowerRange + 1, max);
            for (int i = boundary; i < n; ++i) {
                arr[i] = dist(getRandomEngine());
            }
        } else if constexpr (std::is_floating_point_v<T>) {
            std::uniform_real_distribution<T> dist(maxLowerRange, max);
            for (int i = boundary; i < n; ++i) {
                arr[i] = dist(getRandomEngine());
            }
        }
    }

    static void generatePartiallySorted66(T arr[], int n, T max) {
        static_assert(std::is_arithmetic_v<T>, "Generates data only with numeric types");
        int boundary = (n * 66) / 100;
        T maxLowerRange = static_cast<T>((max * 66) / 100);

        if constexpr (std::is_integral_v<T>) {
            std::uniform_int_distribution<T> dist(0, maxLowerRange);
            for (int i = 0; i < boundary; ++i) {
                arr[i] = dist(getRandomEngine());
            }
        } else if constexpr (std::is_floating_point_v<T>) {
            std::uniform_real_distribution<T> dist(0, maxLowerRange);
            for (int i = 0; i < boundary; ++i) {
                arr[i] = dist(getRandomEngine());
            }
        }

        std::sort(arr, arr + boundary);

        if constexpr (std::is_integral_v<T>) {
            std::uniform_int_distribution<T> dist(maxLowerRange + 1, max);
            for (int i = boundary; i < n; ++i) {
                arr[i] = dist(getRandomEngine());
            }
        } else if constexpr (std::is_floating_point_v<T>) {
            std::uniform_real_distribution<T> dist(maxLowerRange, max);
            for (int i = boundary; i < n; ++i) {
                arr[i] = dist(getRandomEngine());
            }
        }
    }

    static void generateData(DataArrangement arrangement, T arr[], int n, T max) {
        switch (arrangement) {
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
