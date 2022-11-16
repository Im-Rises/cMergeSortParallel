#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include "mergeSortParallelOpenMp.h"
#include "../commonFunctions/commonFunctions.h"

#define INIT_THREADS_NUMBER 4

int main(int argc, char* argv[]) {
    /*
     * Error list:
     * 1 - Error reading line from file
     * 2 - Error allocating memory
     */

    printf("|-----Merge Sort Parallel using OpenMP-----|\n\n");

    printf("Usage: %s < <inputFile> > <outputFile> <threadsNumber>\n", argv[0]);
    printf("Usage: %s < <inputFile> <threadsNumber>\n\n", argv[0]);

    /* Read optional parameters */
    int threadsNumber = INIT_THREADS_NUMBER;
    if (argc != 1)
        threadsNumber = atoi(argv[1]);

    /* Read size of array from stream */
    int arraySize = 0;
    scanf("%d", &arraySize);
    printf("Array size: %d\n", arraySize);

    /* Create array */
    int* inputArray = allocateMemory(arraySize * sizeof(int));

    /* Copy data from stream to array */
    copyStreamToIntArray(inputArray, arraySize);

    /* Start timer */
    clock_t startClock = clock();
    double openMpT = omp_get_wtime();

    /* Sort array */
    mergeSortParallelOpenMp(inputArray, arraySize, threadsNumber);

    /* Stop timers */
    clock_t endClock = clock();
    double openMpTime = (omp_get_wtime() - openMpT);
    printf("CPU and Wall time:\n");
    printf("- CPU time: %f seconds\n", (double)(endClock - startClock) / CLOCKS_PER_SEC);
    printf("- Wall time: %f seconds\n", openMpTime);

    /* Print array is sorted */
    printf("Is array correctly sorted? %s\n", isSorted(inputArray, arraySize) ? "No" : "Yes");

    /* Print array */
    printArraySummary(inputArray, arraySize);

    /* Free memory */
    free(inputArray);

    return 0;
}
