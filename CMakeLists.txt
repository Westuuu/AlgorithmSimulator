cmake_minimum_required(VERSION 3.27)
project(AlgorithmSimulator)

set(CMAKE_CXX_STANDARD 17)

if(WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    
   
endif()

add_executable(AlgorithmSimulator main.cpp
        SortingAlgorithms/InsertionSort.h
        SortingAlgorithms/HeapSort.h
        Data/GenerateData.h
        SortingAlgorithms/ShellSort.h
        Controllers/DataController.h
        Data/DataArrangement.h
        Controllers/ResultsController.cpp
        Controllers/ResultsController.h
        Controllers/SimulationController.h
        Data/PivotStrategy.h
        Data/GapStrategy.h
        SortingAlgorithms/Quicksort.h
        Config/ConfigManager.cpp
        Config/ConfigManager.h
)

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/sorting_results")

configure_file(${CMAKE_SOURCE_DIR}/config.ini ${CMAKE_BINARY_DIR}/config.ini COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/test_data.csv ${CMAKE_BINARY_DIR}/test_data.csv COPYONLY)
