//
// Created by Adam on 15/03/2025.
//

#ifndef AIZO1_GENERATEDATA_H
#define AIZO1_GENERATEDATA_H

#include "random"

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
};


#endif //AIZO1_GENERATEDATA_H
