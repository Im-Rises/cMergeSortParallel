#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#ifdef _OPENMP
#include <omp.h>
#endif

#include "mergeSortSequential.h"
#include "../commonFunctions/commonFunctions.h"

int main(int argc, char* argv[]) {
    /*
     * Error list:
     * 1 - Error reading line from pipe stream
     * 2 - Error allocating memory
     */

    printf("|-----Merge Sort Sequential-----|\n\n");

    printf("Usage: %s < <input file> > <output file> <threads number>\n\n", argv[0]);
    printf("Usage: %s < <input file> > <threads number>\n\n", argv[0]);

    /* Read size of array from stream */
    int arraySize = 0;
    scanf("%d", &arraySize);
    printf("Array size: %d\n", arraySize);

    /* Create array */
    int* inputArray = allocateMemory(arraySize * sizeof(int));
    int* outputArray = allocateMemory(arraySize * sizeof(int));

    /* Copy data from stream to array */
    copyStreamToIntArray(inputArray, arraySize);

    /* Merge sort */
    mergeSort(inputArray, arraySize, outputArray);

    /* Print array is sorted */
    printf("Is array correctly sorted? %s\n", isSorted(outputArray, arraySize) ? "No" : "Yes");

    /* Print array */
    printArraySummary(outputArray, arraySize);

    /* Free memory */
    free(inputArray);
    free(outputArray);

    return 0;
}
