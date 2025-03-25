//
// Created by Adam on 15/03/2025.
//

#ifndef AIZO1_SHELLSORT_H
#define AIZO1_SHELLSORT_H

#include <cmath>
#include "vector"
#include "../Data/GapStrategy.h"

template<typename T>
class ShellSort {
private:
    static std::vector<int> computeSedgewickTerms(int ArraySize) {
        std::vector<int> sedgewickTerms;
        int k = 1;
        sedgewickTerms.push_back(1);

        while (true) {
            int term = static_cast<int>(pow(4, k) + 3 * pow(2, k - 1) + 1);

            if (term > ArraySize) {
                break;
            }

            sedgewickTerms.push_back(term);
            k++;
        }
        return sedgewickTerms;
    }

public:
    static void sort(T arr[], int n, GapStrategy gapStrategy) {
        switch (gapStrategy) {
            case GapStrategy::SHELL: {
                for (int gap = n / 2; gap > 0; gap /= 2) {
                    for (int i = gap; i < n; i++) {
                        T temp = arr[i];

                        int j;
                        for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                            arr[j] = arr[j - gap];
                        }

                        arr[j] = temp;
                    }
                }
                break;
            }
            case GapStrategy::SEDGEWICK: {
                std::vector<int> sedgewickTerms = computeSedgewickTerms(n);

                for (int idx = sedgewickTerms.size() - 1; idx >= 0; idx--) {
                    int gap = sedgewickTerms[idx];
                    for (int i = gap; i < n; ++i) {
                        T temp = arr[i];

                        int j;
                        for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                            arr[j] = arr[j - gap];
                        }

                        arr[j] = temp;
                    }
                }
                break;
            }
        }
    }

};


#endif //AIZO1_SHELLSORT_H
