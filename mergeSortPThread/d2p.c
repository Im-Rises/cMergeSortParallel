#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

#if defined(_OPENMP)
#include <omp.h>
#endif

#define INIT_THREADS_NUMBER 4

#define MAX_NUMBER_PRINT 100
#define COMPLETE_NUMBER_PRINT_THRESHOLD 1000

typedef struct MergeSortArgs MergeSortArgs;

struct MergeSortArgs {
    int* A;
    int size;
    int* B;
};

void mergeSortParallel(int A[], int arraySize, int B[], int threadsNumber);
void* mergeSortThread(void* input);
void mergeSort(int* X, int n, int* tmp);
void merge(int* X, int n, int* tmp);

void* allocateMemory(size_t size);
void printArraySummary(int* array, int arraySize);
void printArray(const int* array, int begin, int size);
int isSorted(const int* array, int arraySize);

int main(int argc, char* argv[]) {
    /*
     * Error list:
     * 1 - Error reading line from file
     * 2 - Error allocating memory
     * 3 - Error creating thread
     */

    printf("|-----Merge Sort Parallel using PThread-----|\n\n");

#ifndef _OPENMP
    printf("You can compile the project with the -fopenmp flag to get elapsed time using OpenMP.\n\n");
#endif

    float start = 0;

    /* Read optional parameters */
    int threadsNumber = INIT_THREADS_NUMBER;
    if (argc != 1)
        threadsNumber = atoi(argv[1]);


    /* Read size of array from stream */
    int arraySize = 0;
    scanf("%d", &arraySize);
    printf("- Array size: %d\n", arraySize);

    /* Create array */
    int* inputArray = allocateMemory(arraySize * sizeof(int));
    int* outputArray = allocateMemory(arraySize * sizeof(int));

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
    printf("Number of threads: %d\n", threadsNumber);

    /* Create timer */
    clock_t clockTimer;
    clockTimer = clock();
#ifdef _OPENMP
    double openMpT = omp_get_wtime();
#endif
    struct timespec timeSpecStart, timeSpecFinish;
    double unixTimelapsed;
    clock_gettime(CLOCK_MONOTONIC, &timeSpecStart);

    /* Sort array */
    mergeSortParallel(inputArray, arraySize, outputArray, threadsNumber);
    /*    mergeSort(inputArray, 0, arraySize - 1);*/

    /* Stop timer */
    clockTimer = clock() - clockTimer;
    double time_taken = ((double)clockTimer) / CLOCKS_PER_SEC; /*calculate the elapsed time*/
#ifdef _OPENMP
    double openMpTime = (omp_get_wtime() - openMpT);
#endif
    clock_gettime(CLOCK_MONOTONIC, &timeSpecFinish);
    unixTimelapsed = (timeSpecFinish.tv_sec - timeSpecStart.tv_sec);
    unixTimelapsed += (timeSpecFinish.tv_nsec - timeSpecStart.tv_nsec) / 1000000000.0;

    /* Print results */
    printf("Time elapsed:\n");
    printf(" - Standard Timer: %f s\n", time_taken);
#ifdef _OPENMP
    printf(" - OpenMP Timer: %f s\n", openMpTime);
#endif
    printf(" - Unix Timer: %f s\n", unixTimelapsed);

    /* Print array is sorted */
    printf("Is input array correctly sorted? %s\n", isSorted(inputArray, arraySize) ? "No" : "Yes");
    printf("Is output array correctly sorted? %s\n", isSorted(outputArray, arraySize) ? "No" : "Yes");

    /* Print array */
    /*printArraySummary(inputArray, arraySize);*/
    printArraySummary(outputArray, arraySize);

    /* Free memory */
    free(inputArray);
    free(outputArray);

    return 0;
}


void mergeSortParallel(int A[], int arraySize, int B[], int threadsNumber) {
    pthread_t threads[threadsNumber];
    MergeSortArgs threadsArgsArray[threadsNumber];
    const int offset = arraySize / threadsNumber;
    int l = 0;
    int i;

    /* Init threads args depending on the number of threads (split parts of the array in each thread) */
    for (i = 0; i < threadsNumber; i++, l += offset)
    {
        threadsArgsArray[i].A = A + l;
        threadsArgsArray[i].B = B + l;
        threadsArgsArray[i].size = offset;
        if (i == threadsNumber - 1)
            threadsArgsArray[i].size += arraySize % threadsNumber;
    }

    /* Merge and sort */
    for (i = 0; i < threadsNumber; i++)
        pthread_create(&threads[i], NULL, mergeSortThread, &threadsArgsArray[i]);
    for (i = 0; i < threadsNumber; i++)
        pthread_join(threads[i], NULL);

    /* Merge work from all threads */
    /*        for (i = 1; i < threadsNumber; i++)
            {
                merge(A, threadsArgsArray[0].p, threadsArgsArray[i].p - 1, threadsArgsArray[i].r);
            }*/

    /*    for (i = 1; i < threadsNumber; i++)
        {
            merge(threadsArgsArray[0].B, threadsArgsArray[i].size * 2, threadsArgsArray[i].B);
        }*/

    /*    mergeSort(A, arraySize, B);*/

    for (i = 1; i < threadsNumber; i++)
    {
        merge(threadsArgsArray[0].B, threadsArgsArray[i].size, threadsArgsArray[i].B);
    }
}

void* mergeSortThread(void* input) {
    mergeSort((*(MergeSortArgs*)input).A, (*(MergeSortArgs*)input).size, (*(MergeSortArgs*)input).B);
    pthread_exit(NULL);
}

void mergeSort(int* X, int n, int* tmp) {
    if (n < 2)
        return;
    mergeSort(X, n / 2, tmp);
    mergeSort(X + n / 2, n - n / 2, tmp);
    merge(X, n, tmp);
}

void merge(int* X, int n, int* tmp) {
    int i = 0;
    int j = n / 2;
    int ti = 0;

    while (i < n / 2 && j < n)
    {
        if (X[i] < X[j])
        {
            tmp[ti] = X[i];
            ti++;
            i++;
        }
        else
        {
            tmp[ti] = X[j];
            ti++;
            j++;
        }
    }
    while (i < n / 2)
    {
        tmp[ti] = X[i];
        ti++;
        i++;
    }
    while (j < n)
    {
        tmp[ti] = X[j];
        ti++;
        j++;
    }
    memcpy(X, tmp, n * sizeof(int));
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

int isSorted(const int* array, int arraySize) {
    int i;
    for (i = 0; i < arraySize - 1; i++)
    {
        if (array[i] > array[i + 1])
        {
            return 1;
        }
    }
    return 0;
}
