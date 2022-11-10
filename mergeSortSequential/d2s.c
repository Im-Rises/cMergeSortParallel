#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>

#if defined(_OPENMP)
#include <omp.h>
#endif

#include "../CommonFunctions/sortFunctions.h"

#define MAX_NUMBER_PRINT 100
#define COMPLETE_NUMBER_PRINT_THRESHOLD 1000

void mergeSort(int A[], int p, int r);
void merge(int A[], int p, int q, int r);

void* allocateMemory(size_t size);
void printArraySummary(int* array, int arraySize);
void printArray(const int* array, int begin, int size);

int main(int argc, char* argv[]) {
    /*
     * Error list:
     * 1 - Wrong number of arguments
     * 2 - Error opening file
     * 3 - Error reading line from file
     * 4 - Error allocating memory
     */
    printf("-----Merge Sort Sequential-----\n\n");

    /* Read size of array from stream */
    int arraySize = 0;
    scanf("%d", &arraySize);
    printf("Array size: %d\n", arraySize);

    /* Create array */
    int* inputArray = allocateMemory(arraySize * sizeof(int));
    /*int* outputArray = allocateMemory(arraySize * sizeof(int));*/

    /* Copy data from stream to array */
    int i;
    for (i = 0; i < arraySize; i++)
    {
        if (scanf("%d", &inputArray[i]) != 1)
        {
            printf("Error reading line from stream");
            return 3;
        }
    }

    /* Start timers */
    clock_t t;
    t = clock();
#ifdef _OPENMP
    double openMpT = omp_get_wtime();
#endif
#ifdef __unix__
    struct timespec timeSpecStart, timeSpecFinish;
    double unixTimelapsed;
    clock_gettime(CLOCK_MONOTONIC, &timeSpecStart);
#endif

    /* Sort array */
    mergeSort(inputArray, 0, arraySize - 1);

    /* Stop timers */
    t = clock() - t;
    double time_taken = ((double)t) / CLOCKS_PER_SEC; /* calculate the elapsed time*/
#ifdef _OPENMP
    double openMpTime = (omp_get_wtime() - openMpT);
#endif
#ifdef __unix__
    clock_gettime(CLOCK_MONOTONIC, &timeSpecFinish);
    unixTimelapsed = (timeSpecFinish.tv_sec - timeSpecStart.tv_sec);
    unixTimelapsed += (timeSpecFinish.tv_nsec - timeSpecStart.tv_nsec) / 1000000000.0;
#endif

    /* Print results */
    printf("Time elapsed:\n");
    printf(" - Standard Timer: %f s\n", time_taken);
#ifdef _OPENMP
    printf(" - OpenMP Timer: %f s\n", openMpTime);
#endif
#ifdef __unix__
    printf(" - Unix Timer: %f s\n", unixTimelapsed);
#endif

    /* Print array is sorted */
    printf("Is array correctly sorted? %s\n", isSorted(inputArray, arraySize) ? "No" : "Yes");

    /* Print array */
    /*    printArraySummary(inputArray, arraySize);*/

    /* free memory */
    free(inputArray);

    return 0;
}

void mergeSort(int A[], int p, int r) {
    if (p < r)
    {
        int q = (p + r) / 2;
        mergeSort(A, p, q);
        mergeSort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

void merge(int A[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;

    int* L = allocateMemory((n1 + 1) * sizeof(int));
    int* R = allocateMemory((n2 + 1) * sizeof(int));
    /*        int L[n1 + 1];
            int R[n2 + 1];*/

    int i, j, k;

    for (i = 0; i < n1; i++)
        L[i] = A[p + i];
    for (j = 0; j < n2; j++)
        R[j] = A[q + j + 1];

    L[n1] = INT_MAX;
    R[n2] = INT_MAX;

    i = 0;
    j = 0;
    for (k = p; k <= r; k++)
    {
        if (L[i] <= R[j])
        {
            A[k] = L[i];
            i++;
        }
        else
        {
            A[k] = R[j];
            j++;
        }
    }
}

void* allocateMemory(size_t size) {
    void* memory = malloc(size);
    if (memory == NULL)
    {
        printf("Error allocating memory");
        exit(4);
    }
    return memory;
}

void printArraySummary(int* array, int arraySize) {
    printf("Array sorted: ");
    if (arraySize > COMPLETE_NUMBER_PRINT_THRESHOLD)
    {
        printf("(Array too big to be printed completely)\n");
        printf("- First %d values: \n", MAX_NUMBER_PRINT);
        printArray(array, 0, MAX_NUMBER_PRINT);
        printf("...\n");
        printf("- Last %d values: \n", MAX_NUMBER_PRINT);
        printArray(array, arraySize - MAX_NUMBER_PRINT, arraySize);
    }
    else
    {
        printf("\n");
        printArray(array, 0, arraySize);
    }
}

void printArray(const int* array, const int begin, const int size) {
    int i;
    for (i = begin; i < size; i++)
        printf("%d\n", array[i]);
}
