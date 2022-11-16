#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

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

    printf("Usage: %s < <inputFile> > <outputFile> <threadsNumber>\n", argv[0]);
    printf("Usage: %s < <inputFile> <threadsNumber>\n\n", argv[0]);

    /* Read optional parameter */
    int threadsNumber = INIT_THREADS_NUMBER; /* include main thread*/
    if (argc != 1)
        threadsNumber = atoi(argv[1]);
    threadsNumber--; /*Main thread is not counted for PThread*/

    /* Read size of array from stream */
    int arraySize = 0;
    scanf("%d", &arraySize);
    printf("- Array size: %d\n", arraySize);

    /* Create array */
    int* array = allocateMemory(arraySize * sizeof(int));

    /* Copy data from stream to array */
    copyStreamToIntArray(array, arraySize);

    /* Print the number of threads */
    printf("Number of threads: %d\n", threadsNumber + 1);

    /* Start timer */
    struct timespec timeSpecStart, timeSpecFinish;
    double unixTimelapsed;
    clock_t startClock = clock();
    clock_gettime(CLOCK_MONOTONIC, &timeSpecStart);

    /* Sort array */
    mergeSortParallelPThread(array, arraySize, threadsNumber);

    /* Stop timer */
    clock_t endClock = clock();
    clock_gettime(CLOCK_MONOTONIC, &timeSpecFinish);
    unixTimelapsed = (timeSpecFinish.tv_sec - timeSpecStart.tv_sec);
    unixTimelapsed += (timeSpecFinish.tv_nsec - timeSpecStart.tv_nsec) / 1000000000.0;
    printf("CPU and Wall time:\n");
    printf("- CPU time: %f seconds\n", (double)(endClock - startClock) / CLOCKS_PER_SEC);
    printf("- Wall time: %f seconds\n", unixTimelapsed);

    /* Print array is sorted */
    printf("Is output array correctly sorted? %s\n", isSorted(array, arraySize) ? "No" : "Yes");

    /* Print array */
    printArraySummary(array, arraySize);

    /* Free memory */
    free(array);

    return 0;
}
