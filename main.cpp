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
    const long long ARRAY_SIZE = 10;
    const int ITERATIONS = 2;
    const long long MAX_VALUE = ARRAY_SIZE;

    ResultsController resultsController;
    {
        DataController<int> dataController(ARRAY_SIZE, MAX_VALUE);
        SimulationController<int> intSimulationController(dataController, resultsController, ITERATIONS);

        // Register sorting algorithms
//        intSimulationController.registerAlgorithm("Insertion Sort", InsertionSort<int>::sort);
//        intSimulationController.registerAlgorithm("Heap Sort", HeapSort<int>::sort);
        intSimulationController.registerAlgorithm("Shellsort - Sedgewick", [](int *arr, int n) {
            ShellSort<int>::sort(arr, n, GapStrategy::SEDGEWICK);
        });
//        intSimulationController.registerAlgorithm("Shellsort - Shell", [](int *arr, int n) {
//            ShellSort<int>::sort(arr, n, GapStrategy::SHELL);
//        });
//
//        intSimulationController.registerAlgorithm("Quicksort - Middle", [](int *arr, int n) {
//            Quicksort<int>::sort(arr, n, PivotStrategy::MIDDLE);
//        });
//
//        intSimulationController.registerAlgorithm("Quicksort - Left", [](int *arr, int n) {
//            Quicksort<int>::sort(arr, n, PivotStrategy::LEFT);
//        });
//        intSimulationController.registerAlgorithm("Quicksort - Right", [](int *arr, int n) {
//            Quicksort<int>::sort(arr, n, PivotStrategy::RIGHT);
//        });
//        intSimulationController.registerAlgorithm("Quicksort - Random", [](int *arr, int n) {
//            Quicksort<int>::sort(arr, n, PivotStrategy::RANDOM);
//        });

        intSimulationController.registerAlgorithm("STL Sort", [](int *arr, int n) {
            std::sort(arr, arr + n);
        });

        // Run the simulation for ints
        cout << "Running simulation with " << ARRAY_SIZE << " elements..." << endl;
        intSimulationController.runSimulation();

    }

    {
        DataController<double> doubleDataController(ARRAY_SIZE, MAX_VALUE);
        SimulationController<double> doubleSimulationController(doubleDataController, resultsController, ITERATIONS);

        doubleSimulationController.registerAlgorithm("Heap sort - double", HeapSort<double>::sort);

        // Run the simulation for doubles
        doubleSimulationController.runSimulation();
    }


    DataController<float> floatDataController(ARRAY_SIZE, MAX_VALUE);
    SimulationController<float> floatSimulationController(floatDataController, resultsController, ITERATIONS);


    // Display results
    cout << "\nSimulation Results:" << endl;
    resultsController.printResults();

    // resultsController.saveResultsToCSV("sorting_results.csv");



    return 0;
}
