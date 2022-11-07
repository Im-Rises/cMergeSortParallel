#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define MAX_THREADS 4

#define MAX_NUMBER_PRINT 100
#define COMPLETE_NUMBER_PRINT_THRESHOLD 1000

void mergeSortParallel(int A[], int p, int r);
void mergeSort(int A[], int p, int r);
void merge(int A[], int p, int q, int r);

void* allocateMemory(size_t size);
void printArraySummary(int* array, int arraySize);
void printArray(const int* array, int begin, int size);

/* void swap(int* a, int* b);
 int binarySearch(int x, int T[], int p, int r);
 void parallelMerge(int T[], int p1, int r1, int p2, int r2, int A[], int p3);
 void parallelMergeSort(int A[], int p, int r, int B[], int s);*/

int main() {
    /*
     * Error list:
     * 1 - Error reading line from file
     * 2 - Error allocating memory
     */

    printf("-----Merge Sort Parallel using OpenMP-----\n\n");

    /* Read size of array from stream */
    int arraySize = 0;
    scanf("%d", &arraySize);
    printf("- Array size: %d\n", arraySize);

    /* Create array */
    int* inputArray = allocateMemory(arraySize * sizeof(int));

    /* Copy data from stream to array */
    int i;
    for (i = 0; i < arraySize; i++)
    {
        if (scanf("%d", &inputArray[i]) != 1)
        {
            fprintf(stderr, "Error reading line from stream");
            return 1;
        }
    }

    /* Print the number of threads */
    /*        omp_set_num_threads(MAX_THREADS);
        omp_set_num_threads(omp_get_max_threads());*/
    printf("Number of threads: %d\n", omp_get_max_threads());

    clock_t clockTimer;
    clockTimer = clock();
    printf("Merge sort timer starts\n");

    mergeSortParallel(inputArray, 0, arraySize - 1);

    clockTimer = clock() - clockTimer;
    double time_taken = ((double)clockTimer) / CLOCKS_PER_SEC; /*calculate the elapsed time*/
    printf("The merge sort took %f seconds to execute\n", time_taken);

    /* Print array */
    printArraySummary(inputArray, arraySize);

    free(inputArray);

    return 0;
}

void mergeSortParallel(int A[], int p, int r) {
    if (p < r)
    {
        int q = (p + r) / 2;

#pragma omp task shared(A) private(p, r)
        mergeSort(A, p, q);
#pragma omp task shared(A) private(p, r)
        mergeSort(A, q + 1, r);
#pragma omp taskwait
        merge(A, p, q, r);
    }
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
    int i, j, k;

    int n1 = q - p + 1;
    int n2 = r - q;

    int L[n1 + 1];
    int R[n2 + 1];

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
        fprintf(stderr, "Error allocating memory");
        exit(2);
    }
    return memory;
}

void printArraySummary(int* array, int arraySize) {
    printf("Array sorted:\n");
    if (arraySize > COMPLETE_NUMBER_PRINT_THRESHOLD)
    {
        printf("Array too big to print\n");
        printf("- First %d values: \n", MAX_NUMBER_PRINT);
        printArray(array, 0, 100);
        printf("...\n");
        printf("- Last %d values: \n", MAX_NUMBER_PRINT);
        printArray(array, arraySize - 100, arraySize);
    }
    else
    {
        printArray(array, 0, arraySize);
    }
}

void printArray(const int* array, const int begin, const int size) {
    int i;
    for (i = begin; i < size; i++)
        printf("%d\n", array[i]);
    printf("\n");
}
