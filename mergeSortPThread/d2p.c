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

#define MULTITHREAD_THRESHOLD 1000

/*typedef enum Boolean Boolean;*/
enum Boolean {
    False = 0,
    True = 1
};

typedef struct ThreadState ThreadState;
struct ThreadState {
    pthread_t thread;
    enum Boolean isUsed;
};

typedef struct MergeSortArgs MergeSortArgs;
struct MergeSortArgs {
    int* A;
    int size;
    int* B;
    ThreadState* threads;
    int threadsNumber;
};

void mergeSortParallel(int A[], int arraySize, int B[], int threadsNumber);
void mergeSortParallelPthread(int A[], int arraySize, int B[], ThreadState* threads, int threadsNumber);
void* mergeSortParallelPthreadThread(void* input);
void mergeSort(int* X, int n, int* tmp);
void merge(int* X, int n, int* tmp);

int checkThreadsAvailable(ThreadState* threads, int threadsNumber);

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

    threadsNumber--;


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
    printf("Number of threads: %d\n", threadsNumber + 1);

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
    printf("Is output array correctly sorted? %s\n", isSorted(outputArray, arraySize) ? "No" : "Yes");

    /* Print array */
    printArraySummary(outputArray, arraySize);

    /* Free memory */
    free(inputArray);
    free(outputArray);

    return 0;
}

void mergeSortParallel(int A[], int arraySize, int B[], int threadsNumber) {
    ThreadState threads[threadsNumber];
    int i;
    for (i = 0; i < threadsNumber; i++)
    {
        threads[i].isUsed = False;
    }

    mergeSortParallelPthread(A, arraySize, B, threads, threadsNumber);
}

void mergeSortParallelPthread(int A[], int arraySize, int B[], ThreadState* threads, int threadsNumber) {
    /* if array is too small do mono-thread merge sort*/
    if (arraySize < MULTITHREAD_THRESHOLD)
    {
        mergeSort(A, arraySize, B);
        return;
    }

    /* if a thread is available use it*/
    int threadIndex = checkThreadsAvailable(threads, threadsNumber);

    if (threadIndex != -1)
    {
        threads[threadIndex].isUsed = True;
        MergeSortArgs args = {
            A,
            arraySize / 2,
            B,
            threads,
            threadsNumber
        };

        /* create thread*/
        if (pthread_create(&threads[threadIndex].thread, NULL, mergeSortParallelPthreadThread, &args) != 0)
        {
            fprintf(stderr, "Error creating thread");
            exit(3);
        }

        /* sort the other half of the array*/
        mergeSortParallelPthread(A + arraySize / 2, arraySize - arraySize / 2, B + arraySize / 2, threads, threadsNumber);

        /* wait for the thread to finish*/
        pthread_join(threads[threadIndex].thread, NULL);
        threads[threadIndex].isUsed = False;

        /* merge the two sorted arrays*/
        merge(A, arraySize, B);
    }
    else
    {
        /* if no thread is available do mono-thread merge sort*/
        mergeSortParallelPthread(A, arraySize / 2, B, threads, threadsNumber);
        mergeSortParallelPthread(A + arraySize / 2, arraySize - arraySize / 2, B + arraySize / 2, threads, threadsNumber);
        merge(A, arraySize, B);
    }
}

int checkThreadsAvailable(ThreadState* threads, int threadsNumber) {
    int index;
    for (index = 0; index < threadsNumber; index++)
    {
        if (threads[index].isUsed == False)
            return index;
    }
    return -1;
}

void* mergeSortParallelPthreadThread(void* input) {
    mergeSortParallelPthread((*(MergeSortArgs*)input).A, (*(MergeSortArgs*)input).size, (*(MergeSortArgs*)input).B, (*(MergeSortArgs*)input).threads, (*(MergeSortArgs*)input).threadsNumber);
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
