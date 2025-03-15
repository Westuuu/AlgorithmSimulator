cmake_minimum_required(VERSION 3.27)
project(Aizo1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Aizo1 main.cpp
        SortingAlgorithms/InsertionSort.h
        SortingAlgorithms/HeapSort.h
        Data/GenerateData.h
        SortingAlgorithms/ShellSort.h
        Data/ValidateIfSorted.h
        Data/SortingDataManager.h
)
