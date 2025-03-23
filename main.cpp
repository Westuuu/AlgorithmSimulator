#include <iostream>
#include "SortingAlgorithms/InsertionSort.h"
#include "SortingAlgorithms/HeapSort.h"
#include "Data/GenerateData.h"
#include "Controllers/DataController.h"
#include "SortingAlgorithms/ShellSort.h"
#include "Controllers/ResultsController.h"
#include "Controllers/SimulationController.h"
#include "SortingAlgorithms/Quicksort.h"

using namespace std;


int main() {
    const int ARRAY_SIZE = 20;
    const int ITERATIONS = 5;
    const int MAX_VALUE = ARRAY_SIZE;

    ResultsController resultsController;
    DataController<int> dataController(ARRAY_SIZE, MAX_VALUE);
    SimulationController<int> simulationController(dataController, resultsController);


    // Register sorting algorithms
//    simulationController.registerAlgorithm("Insertion Sort", InsertionSort<int>::sort);
//    simulationController.registerAlgorithm("Heap Sort", HeapSort<int>::sort);
    simulationController.registerAlgorithm("Shellsort - Sedgewick", [](int *arr, int n) {
        ShellSort<int>::sort(arr, n, GapStrategy::SEDGEWICK);
    });
    simulationController.registerAlgorithm("Shellsort - Shell", [](int *arr, int n) {
        ShellSort<int>::sort(arr, n, GapStrategy::SHELL);
    });

//    simulationController.registerAlgorithm("Heap sort - double", HeapSort<double>::sort);

    simulationController.registerAlgorithm("Quicksort - Middle", [](int *arr, int n) {
        Quicksort<int>::sort(arr, n, PivotStrategy::MIDDLE);
    });
//
//    simulationController.registerAlgorithm("Quicksort - Left", [](int *arr, int n) {
//        Quicksort<int>::sort(arr, n, PivotStrategy::LEFT);
//    });
//    simulationController.registerAlgorithm("Quicksort - Right", [](int *arr, int n) {
//        Quicksort<int>::sort(arr, n, PivotStrategy::RIGHT);
//    });
//    simulationController.registerAlgorithm("Quicksort - Random", [](int *arr, int n) {
//        Quicksort<int>::sort(arr, n, PivotStrategy::RANDOM);
//    });

    simulationController.registerAlgorithm("STL Sort", [](int *arr, int n) {
        std::sort(arr, arr + n);
    });


    // simulationController.ITERATIONS = ITERATIONS;

    // Run the simulation
    cout << "Running simulation with " << ARRAY_SIZE << " elements..." << endl;
    simulationController.runSimulation();

    // Display results
    cout << "\nSimulation Results:" << endl;
    resultsController.printResults();

    // resultsController.saveResultsToCSV("sorting_results.csv");



    return 0;
}
