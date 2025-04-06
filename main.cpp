#include <iostream>

#include "Config/ConfigManager.h"
#include "SortingAlgorithms/InsertionSort.h"
#include "SortingAlgorithms/HeapSort.h"
#include "Controllers/DataController.h"
#include "SortingAlgorithms/ShellSort.h"
#include "Controllers/ResultsController.h"
#include "Controllers/SimulationController.h"
#include "SortingAlgorithms/Quicksort.h"

using namespace std;
namespace fs = std::filesystem;


int main() {
    auto config = ConfigManager::getInstance();
    fs::path configPath = fs::path("config.ini");
    if (!config->loadConfig(configPath.string())) {
        cerr << "Config file not found" << endl;
        configPath = fs::path("..") / "config.ini";
        if (!config->loadConfig(configPath.string())) {
            cerr << "Config file not found in alternative location either" << endl;
            return 1;
        }
    }

    const int ARRAY_SIZE = config->getInt("ARRAY_SIZE", 30000);
    const int ITERATIONS = config->getInt("ITERATIONS", 1);
    const int MAX_VALUE = config->getInt("MAX_VALUE", ARRAY_SIZE);

    const bool USE_INT_DATA = config->getBool("USE_INT_DATA", true);
    const bool USE_DOUBLE_DATA = config->getBool("USE_DOUBLE_DATA", true);
    const bool USE_FLOAT_DATA = config->getBool("USE_FLOAT_DATA", true);

    const bool ENABLE_INSERTION_SORT = config->getBool("ENABLE_INSERTION_SORT", true);
    const bool ENABLE_HEAP_SORT = config->getBool("ENABLE_HEAP_SORT", true);
    const bool ENABLE_SHELL_SORT_SHELL = config->getBool("ENABLE_SHELL_SORT_SHELL", true);
    const bool ENABLE_SHELL_SORT_SEDGEWICK = config->getBool("ENABLE_SHELL_SORT_SEDGEWICK", true);
    const bool ENABLE_QUICKSORT_LEFT = config->getBool("ENABLE_QUICKSORT_LEFT", true);
    const bool ENABLE_QUICKSORT_RIGHT = config->getBool("ENABLE_QUICKSORT_RIGHT", true);
    const bool ENABLE_QUICKSORT_MIDDLE = config->getBool("ENABLE_QUICKSORT_MIDDLE", true);
    const bool ENABLE_QUICKSORT_RANDOM = config->getBool("ENABLE_QUICKSORT_RANDOM", true);

    const bool TEST_MODE = config->getBool("TEST_MODE", false);
    const string TEST_DATA_FILE = config->getString("TEST_DATA_FILE", "test_data.csv");

    const bool PRINT_EACH_RESULT = config->getBool("PRINT_EACH_RESULT", true);
    const bool SAVE_TO_CSV = config->getBool("SAVE_TO_CSV", false);
    const string CSV_DIRECTORY = config->getString("CSV_DIRECTORY", "results");


    ResultsController resultsController;
    if (USE_INT_DATA) {
        DataController<int> intDataController(ARRAY_SIZE, MAX_VALUE);
        SimulationController<int> intSimulationController(intDataController, resultsController, ITERATIONS,
                                                          PRINT_EACH_RESULT, SAVE_TO_CSV, CSV_DIRECTORY,
                                                          TEST_MODE, TEST_DATA_FILE);

        if (ENABLE_INSERTION_SORT) {
            intSimulationController.registerAlgorithm("Insertion Sort - int", InsertionSort<int>::sort);
        }
        if (ENABLE_HEAP_SORT) {
            intSimulationController.registerAlgorithm("Heap sort - int", HeapSort<int>::sort);
        }
        if (ENABLE_SHELL_SORT_SEDGEWICK) {
            intSimulationController.registerAlgorithm("Shellsort - Sedgewick - int", [](int *arr, int n) {
                ShellSort<int>::sort(arr, n, GapStrategy::SEDGEWICK);
            });
        }
        if (ENABLE_SHELL_SORT_SHELL) {
            intSimulationController.registerAlgorithm("Shellsort - Shell - int", [](int *arr, int n) {
                ShellSort<int>::sort(arr, n, GapStrategy::SHELL);
            });
        }

        if (ENABLE_QUICKSORT_MIDDLE) {
            intSimulationController.registerAlgorithm("Quicksort - Middle - int", [](int *arr, int n) {
                Quicksort<int>::sort(arr, n, PivotStrategy::MIDDLE);
            });
        }
        if (ENABLE_QUICKSORT_LEFT) {
            intSimulationController.registerAlgorithm("Quicksort - Left - int", [](int *arr, int n) {
                Quicksort<int>::sort(arr, n, PivotStrategy::LEFT);
            });
        }
        if (ENABLE_QUICKSORT_RIGHT) {
            intSimulationController.registerAlgorithm("Quicksort - Right - int", [](int *arr, int n) {
                Quicksort<int>::sort(arr, n, PivotStrategy::RIGHT);
            });
        }
        if (ENABLE_QUICKSORT_RANDOM) {
            intSimulationController.registerAlgorithm("Quicksort - Random - int", [](int *arr, int n) {
                Quicksort<int>::sort(arr, n, PivotStrategy::RANDOM);
            });
        }

        cout << "Running simulation for int data type with " << ARRAY_SIZE << " elements..." << endl;
        intSimulationController.runSimulation();
    }
    
    if (USE_DOUBLE_DATA) {
        DataController<double> doubleDataController(ARRAY_SIZE, MAX_VALUE);
        SimulationController<double> doubleSimulationController(doubleDataController, resultsController, ITERATIONS,
                                                                PRINT_EACH_RESULT, SAVE_TO_CSV, CSV_DIRECTORY);

        if (ENABLE_INSERTION_SORT) {
            doubleSimulationController.registerAlgorithm("Insertion Sort - double", InsertionSort<double>::sort);
        }
        if (ENABLE_HEAP_SORT) {
            doubleSimulationController.registerAlgorithm("Heap sort - double", HeapSort<double>::sort);
        }
        if (ENABLE_SHELL_SORT_SEDGEWICK) {
            doubleSimulationController.registerAlgorithm("Shellsort - Sedgewick - double", [](double *arr, int n) {
                ShellSort<double>::sort(arr, n, GapStrategy::SEDGEWICK);
            });
        }
        if (ENABLE_SHELL_SORT_SHELL) {
            doubleSimulationController.registerAlgorithm("Shellsort - Shell - double", [](double *arr, int n) {
                ShellSort<double>::sort(arr, n, GapStrategy::SHELL);
            });
        }
        if (ENABLE_QUICKSORT_MIDDLE) {
            doubleSimulationController.registerAlgorithm("Quicksort - Middle - double", [](double *arr, int n) {
                Quicksort<double>::sort(arr, n, PivotStrategy::MIDDLE);
            });
        }
        if (ENABLE_QUICKSORT_LEFT) {
            doubleSimulationController.registerAlgorithm("Quicksort - Left - double", [](double *arr, int n) {
                Quicksort<double>::sort(arr, n, PivotStrategy::LEFT);
            });
        }
        if (ENABLE_QUICKSORT_RIGHT) {
            doubleSimulationController.registerAlgorithm("Quicksort - Right - double", [](double *arr, int n) {
                Quicksort<double>::sort(arr, n, PivotStrategy::RIGHT);
            });
        }
        if (ENABLE_QUICKSORT_RANDOM) {
            doubleSimulationController.registerAlgorithm("Quicksort - Random - double", [](double *arr, int n) {
                Quicksort<double>::sort(arr, n, PivotStrategy::RANDOM);
            });
        }

        cout << "Running simulation for double data type with " << ARRAY_SIZE << " elements..." << endl;
        doubleSimulationController.runSimulation();
    }
    
    if (USE_FLOAT_DATA) {
        DataController<float> floatDataController(ARRAY_SIZE, MAX_VALUE);
        SimulationController<float> floatSimulationController(floatDataController, resultsController, ITERATIONS,
                                                              PRINT_EACH_RESULT, SAVE_TO_CSV, CSV_DIRECTORY);

        if (ENABLE_INSERTION_SORT) {
            floatSimulationController.registerAlgorithm("Insertion Sort - float", InsertionSort<float>::sort);
        }
        if (ENABLE_HEAP_SORT) {
            floatSimulationController.registerAlgorithm("Heap sort - float", HeapSort<float>::sort);
        }
        if (ENABLE_SHELL_SORT_SEDGEWICK) {
            floatSimulationController.registerAlgorithm("Shellsort - Sedgewick - float", [](float *arr, int n) {
                ShellSort<float>::sort(arr, n, GapStrategy::SEDGEWICK);
            });
        }
        if (ENABLE_SHELL_SORT_SHELL) {
            floatSimulationController.registerAlgorithm("Shellsort - Shell - float", [](float *arr, int n) {
                ShellSort<float>::sort(arr, n, GapStrategy::SHELL);
            });
        }
        if (ENABLE_QUICKSORT_MIDDLE) {
            floatSimulationController.registerAlgorithm("Quicksort - Middle - float", [](float *arr, int n) {
                Quicksort<float>::sort(arr, n, PivotStrategy::MIDDLE);
            });
        }
        if (ENABLE_QUICKSORT_LEFT) {
            floatSimulationController.registerAlgorithm("Quicksort - Left - float", [](float *arr, int n) {
                Quicksort<float>::sort(arr, n, PivotStrategy::LEFT);
            });
        }
        if (ENABLE_QUICKSORT_RIGHT) {
            floatSimulationController.registerAlgorithm("Quicksort - Right - float", [](float *arr, int n) {
                Quicksort<float>::sort(arr, n, PivotStrategy::RIGHT);
            });
        }
        if (ENABLE_QUICKSORT_RANDOM) {
            floatSimulationController.registerAlgorithm("Quicksort - Random - float", [](float *arr, int n) {
                Quicksort<float>::sort(arr, n, PivotStrategy::RANDOM);
            });
        }

        cout << "Running simulation for float data type with " << ARRAY_SIZE << " elements..." << endl;
        floatSimulationController.runSimulation();
    }

    // Display results
    cout << "\nSimulation Results:" << endl;
    resultsController.printResults();
    resultsController.printStatisticsByAlgorithmAndArrangement();

    return 0;
}
