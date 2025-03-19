cmake_minimum_required(VERSION 3.27)
project(Aizo1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Aizo1 main.cpp
        SortingAlgorithms/InsertionSort.h
        SortingAlgorithms/HeapSort.h
        Data/GenerateData.h
        SortingAlgorithms/ShellSort.h
        Controllers/SortingDataController.h
        Data/DataArrangement.h
        Controllers/ResultsController.cpp
        Controllers/ResultsController.h
        Controllers/SimulationController.h
        Data/PivotStrategy.h
        Data/GapStrategy.h
        SortingAlgorithms/Quicksort.h
)
