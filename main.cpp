#include <iostream>
#include "SortingAlgorithms/InsertionSort.h"
#include "SortingAlgorithms/HeapSort.h"
#include "Data/GenerateData.h"
#include "Controllers/SortingDataController.h"
#include "SortingAlgorithms/ShellSort.h"
#include "Controllers/ResultsController.h"
#include "Controllers/SimulationController.h"

using namespace std;

int main() {
    const int ARRAY_SIZE = 10000;
    const int ITERATIONS = 5;
    const int MAX_VALUE = ARRAY_SIZE;

    ResultsController resultsController;
    SortingDataController<int> dataController(ARRAY_SIZE, MAX_VALUE);
    SimulationController<int> simulationController(dataController, resultsController);

    // Register sorting algorithms
    simulationController.registerAlgorithm("Insertion Sort", InsertionSort<int>::sort);
    simulationController.registerAlgorithm("Heap Sort", HeapSort<int>::sort);

    // Set number of iterations (optional if you want to change the default)
    // simulationController.ITERATIONS = ITERATIONS;  // You'll need to make ITERATIONS public or add a setter

    // Run the simulation
    cout << "Running simulation with " << ARRAY_SIZE << " elements..." << endl;
    simulationController.runSimulation();

    // Display results
    cout << "\nSimulation Results:" << endl;
    resultsController.printResults();

    // Optional: Export results to CSV
    // resultsController.exportToCSV("sorting_results.csv");

    return 0;
}
