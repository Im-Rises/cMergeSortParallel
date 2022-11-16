#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "mergeSortSequential.h"
#include "../commonFunctions/commonFunctions.h"

int main(int argc, char* argv[]) {
    /*
     * Error list:
     * 1 - Error reading line from pipe stream
     * 2 - Error allocating memory
     */

    printf("|-----Merge Sort Sequential-----|\n\n");

    printf("Usage: %s < <input file> > <output file> <threads number>\n", argv[0]);
    printf("Usage: %s < <input file> > <threads number>\n\n", argv[0]);

    /* Read size of array from stream */
    int arraySize = 0;
    scanf("%d", &arraySize);
    printf("Array size: %d\n", arraySize);

    /* Create array */
    int* array = allocateMemory(arraySize * sizeof(int));

    /* Copy data from stream to array */
    copyStreamToIntArray(array, arraySize);

    /* Start timer */
    clock_t startClock = clock();

    /* Merge sort */
    mergeSortSequential(array, arraySize);

    /* Stop timer */
    clock_t endClock = clock();
    printf("Wall time and CPU time: %f seconds\n", (double)(endClock - startClock) / CLOCKS_PER_SEC);

    /* Print array is sorted */
    printf("Is array correctly sorted? %s\n", isSorted(array, arraySize) ? "No" : "Yes");

    /* Print array */
    printArraySummary(array, arraySize);

    /* Free memory */
    free(array);

    return 0;
}
