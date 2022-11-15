#include <stdio.h>
#include <stdlib.h>

#include "mergeSortParallelPThread.h"
#include "../commonFunctions/commonFunctions.h"

#define INIT_THREADS_NUMBER 4

int main(int argc, char* argv[]) {
    /*
     * Error list:
     * 1 - Error reading line from file
     * 2 - Error allocating memory
     * 3 - Error creating thread
     */

    printf("|-----Merge Sort Parallel using PThread-----|\n\n");

    printf("Usage: %s < <input file> > <output file> <threads number>\n\n", argv[0]);
    printf("Usage: %s < <input file> > <threads number>\n\n", argv[0]);

    /* Read optional parameter */
    int threadsNumber = INIT_THREADS_NUMBER; // include main thread
    if (argc != 1)
        threadsNumber = atoi(argv[1]);
    threadsNumber--; // Main thread is not counted for PThread

    /* Read size of array from stream */
    int arraySize = 0;
    scanf("%d", &arraySize);
    printf("- Array size: %d\n", arraySize);

    /* Create array */
    int* inputArray = allocateMemory(arraySize * sizeof(int));
    int* outputArray = allocateMemory(arraySize * sizeof(int));

    /* Copy data from stream to array */
    copyStreamToIntArray(inputArray, arraySize);

    /* Print the number of threads */
    printf("Number of threads: %d\n", threadsNumber + 1);

    /* Sort array */
    mergeSortParallelPThread(inputArray, arraySize, outputArray, threadsNumber);

    /* Print array is sorted */
    printf("Is output array correctly sorted? %s\n", isSorted(outputArray, arraySize) ? "No" : "Yes");

    /* Print array */
    printArraySummary(outputArray, arraySize);

    /* Free memory */
    free(inputArray);
    free(outputArray);

    return 0;
}
