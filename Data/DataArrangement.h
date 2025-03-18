//
// Created by Adam on 16/03/2025.
//

#ifndef AIZO1_DATAARRANGEMENT_H
#define AIZO1_DATAARRANGEMENT_H

enum class DataArrangement {
    FULLY_SORTED_ASCENDING,
    FULLY_SORTED_DESCENDING,
    PARTIALLY_SORTED_33,
    PARTIALLY_SORTED_66,
    RANDOM
};

inline std::vector<DataArrangement> getDataArrangements() {
    return {
            DataArrangement::FULLY_SORTED_ASCENDING,
            DataArrangement::FULLY_SORTED_DESCENDING,
            DataArrangement::PARTIALLY_SORTED_33,
            DataArrangement::PARTIALLY_SORTED_66,
            DataArrangement::RANDOM
    };
};

#endif //AIZO1_DATAARRANGEMENT_H
