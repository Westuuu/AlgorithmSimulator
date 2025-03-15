//
// Created by Adam on 15/03/2025.
//

#ifndef AIZO1_VALIDATEIFSORTED_H
#define AIZO1_VALIDATEIFSORTED_H

template<typename T>
class ValidateIfSorted {
public:
    static bool checkIfSortedASC(T arr[], int n) {
        for (int i = 1; i < n; ++i) {
            if (arr[i] < arr[i - 1]) {
                return false;
            }
        }
        return true;
    }
};

#endif //AIZO1_VALIDATEIFSORTED_H
