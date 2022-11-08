#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include "../test/sortFunctions.h"

#define THREADS_NUMBER 2

#define MAX_NUMBER_PRINT 100
#define COMPLETE_NUMBER_PRINT_THRESHOLD 1000

typedef struct MergeSortArgs MergeSortArgs;

struct MergeSortArgs {
    int* A;
    int p;
    int r;
};

void mergeSortParallel(int A[], int arraySize);
void* mergeSortThread(void* input);
void mergeSort(int A[], int p, int r);
void merge(int A[], int p, int q, int r);

void* allocateMemory(size_t size);
void printArraySummary(int* array, int arraySize);
void printArray(const int* array, int begin, int size);

int main() {
    /*
     * Error list:
     * 1 - Error reading line from file
     * 2 - Error allocating memory
     * 3 - Error creating thread
     */

    printf("|-----Merge Sort Parallel using PThread-----|\n\n");

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
    printf("Number of threads: %d\n", THREADS_NUMBER);

    /* Create timer */
    clock_t clockTimer;
    clockTimer = clock();
    printf("Merge sort timer starts\n");

    /* Sort array */
    mergeSortParallel(inputArray, arraySize);

    /* Stop timer */
    clockTimer = clock() - clockTimer;
    double time_taken = ((double)clockTimer) / CLOCKS_PER_SEC; /*calculate the elapsed time*/
    printf("The merge sort took %f seconds to execute\n", time_taken);

    /* Print array is sorted */
    printf("Is array correctly sorted? %s\n", isSorted(inputArray, arraySize) ? "No" : "Yes");

    /* Print array */
    printArraySummary(inputArray, arraySize);

    /* Free memory */
    free(inputArray);

    return 0;
}


void mergeSortParallel(int A[], const int arraySize) {
    pthread_t threads[THREADS_NUMBER];
    MergeSortArgs threadsArgsArray[THREADS_NUMBER];
    const int offset = arraySize / THREADS_NUMBER;
    int l = 0;
    int i;

    /* Init threads args depending on the number of threads (split parts of the array in each threads) */
    for (i = 0; i < THREADS_NUMBER; i++, l += offset)
    {
        threadsArgsArray[i].A = A;
        threadsArgsArray[i].p = l;
        threadsArgsArray[i].r = l + offset - 1;
        if (i == (THREADS_NUMBER - 1))
            threadsArgsArray[i].r = arraySize - 1;
    }

    /* Merge and sort */
    for (i = 0; i < THREADS_NUMBER; i++)
        pthread_create(&threads[i], NULL, mergeSortThread, &threadsArgsArray[i]);
    for (i = 0; i < THREADS_NUMBER; i++)
        pthread_join(threads[i], NULL);

    /* Merge work from all threads */
    for (i = 1; i < THREADS_NUMBER; i++)
    {
        merge(A, threadsArgsArray[0].p, threadsArgsArray[i].p - 1, threadsArgsArray[i].r);
    }
}

void* mergeSortThread(void* input) {
    mergeSort((*(MergeSortArgs*)input).A, (*(MergeSortArgs*)input).p, (*(MergeSortArgs*)input).r);
    pthread_exit(NULL);
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
        printArray(array, 0, MAX_NUMBER_PRINT);
        printf("...\n");
        printf("- Last %d values: \n", MAX_NUMBER_PRINT);
        printArray(array, arraySize - MAX_NUMBER_PRINT, arraySize);
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
}
