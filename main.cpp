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
    const int ARRAY_SIZE = 80000;
    const int ITERATIONS = 50;
    const int MAX_VALUE = 40000;


    ResultsController resultsController;
    {
        DataController<int> intDataController(ARRAY_SIZE, MAX_VALUE);
        SimulationController<int> intSimulationController(intDataController, resultsController, ITERATIONS);
        // intSimulationController.setPrintResultFlag(true);

        // Register sorting algorithms
       intSimulationController.registerAlgorithm("Insertion Sort - int", InsertionSort<int>::sort);
        intSimulationController.registerAlgorithm("Heap sort - int", HeapSort<int>::sort);
        intSimulationController.registerAlgorithm("Shellsort - Sedgewick - int", [](int *arr, int n) {
            ShellSort<int>::sort(arr, n, GapStrategy::SEDGEWICK);
        });
        intSimulationController.registerAlgorithm("Shellsort - Shell - int", [](int *arr, int n) {
            ShellSort<int>::sort(arr, n, GapStrategy::SHELL);
        });

        intSimulationController.registerAlgorithm("Quicksort - Middle - int", [](int *arr, int n) {
            Quicksort<int>::sort(arr, n, PivotStrategy::MIDDLE);
        });
        //
        intSimulationController.registerAlgorithm("Quicksort - Left - int", [](int *arr, int n) {
            Quicksort<int>::sort(arr, n, PivotStrategy::LEFT);
        });
        intSimulationController.registerAlgorithm("Quicksort - Right - int", [](int *arr, int n) {
            Quicksort<int>::sort(arr, n, PivotStrategy::RIGHT);
        });
        intSimulationController.registerAlgorithm("Quicksort - Random - int", [](int *arr, int n) {
            Quicksort<int>::sort(arr, n, PivotStrategy::RANDOM);
        });

        // intSimulationController.registerAlgorithm("STL Sort", [](int *arr, int n) {
        //     std::sort(arr, arr + n);
        // });

        // Run the simulation for ints
        cout << "Running simulation with " << ARRAY_SIZE << " elements..." << endl;
        intSimulationController.runSimulation();

    }

    {
        DataController<double> doubleDataController(ARRAY_SIZE, MAX_VALUE);
        SimulationController<double> doubleSimulationController(doubleDataController, resultsController, ITERATIONS);

        doubleSimulationController.registerAlgorithm("Heap sort - double", HeapSort<double>::sort);
        doubleSimulationController.registerAlgorithm("Shellsort - Sedgewick - double", [](double *arr, int n) {
            ShellSort<double>::sort(arr, n, GapStrategy::SEDGEWICK);
        });

        // Run the simulation for doubles
        doubleSimulationController.runSimulation();
    }


    {
        DataController<float> floatDataController(ARRAY_SIZE, MAX_VALUE);
        SimulationController<float> floatSimulationController(floatDataController, resultsController, ITERATIONS);
        floatSimulationController.setPrintResultFlag(true);

        floatSimulationController.registerAlgorithm("Heap sort - float", HeapSort<float>::sort);
        floatSimulationController.registerAlgorithm("Shellsort - Sedgewick - float", [](float *arr, int n) {
            ShellSort<float>::sort(arr, n, GapStrategy::SEDGEWICK);
        });

        floatSimulationController.runSimulation();
    }

    // Display results
    cout << "\nSimulation Results:" << endl;
    resultsController.printResults();

    return 0;
}
