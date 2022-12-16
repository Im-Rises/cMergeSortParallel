#include "mergeSortParallelPThread.h"

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "../mergeSortSequential/mergeSortSequential.h"
#include "../commonFunctions/commonFunctions.h"


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

typedef struct MergeSortThreadArgs MergeSortThreadArgs;
struct MergeSortThreadArgs {
    int* A;
    int size;
    int* B;
    ThreadState* threads;
    int threadsNumber;
    pthread_mutex_t* myMutex;
};

void mergeSortParallel(int array[], int arraySize, int bufferArray[], ThreadState* threads, int threadsNumber, pthread_mutex_t* myMutex);
int checkThreadIsAvailable(ThreadState* threads, int threadsNumber);
void* mergeSortParallelThread(void* input);

void mergeSortParallelPThread(int array[], int arraySize, int threadsNumber) {
    ThreadState threads[threadsNumber];
    int i;
    for (i = 0; i < threadsNumber; i++)
    {
        threads[i].isUsed = False;
    }

    pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;

    int* bufferArray = allocateMemory(arraySize * sizeof(int));
    mergeSortParallel(array, arraySize, bufferArray, threads, threadsNumber, &myMutex);

    free(bufferArray);
}

void mergeSortParallel(int array[], int arraySize, int bufferArray[], ThreadState* threads, int threadsNumber, pthread_mutex_t* myMutex) {
    /* if array is too small do mono-thread merge sort*/
    if (arraySize < MULTITHREAD_THRESHOLD)
    {
        mergeSort(array, arraySize, bufferArray);
        return;
    }

    /* if a thread is available get index */
    int threadIndex = -1;
    pthread_mutex_lock(myMutex);
    threadIndex = checkThreadIsAvailable(threads, threadsNumber);
    if (threadIndex != -1)
    {
        threads[threadIndex].isUsed = True;
    }
    pthread_mutex_unlock(myMutex);

    if (threadIndex != -1)
    {
        /* if a thread is available use it */
        MergeSortThreadArgs args = {
            array,
            arraySize / 2,
            bufferArray,
            threads,
            threadsNumber,
            myMutex
        };

        /* create thread*/
        if (pthread_create(&threads[threadIndex].thread, NULL, mergeSortParallelThread, &args) != 0)
        {
            fprintf(stderr, "Error creating thread");
            exit(3);
        }

        /* sort the other half of the array*/
        mergeSortParallel(array + arraySize / 2, arraySize - arraySize / 2, bufferArray + arraySize / 2, threads, threadsNumber, myMutex);

        /* wait for the thread to finish*/
        pthread_join(threads[threadIndex].thread, NULL);

        /* Free the thread to use*/
        threads[threadIndex].isUsed = False;

        /* merge the two sorted arrays*/
        merge(array, arraySize, bufferArray);
    }
    else
    {
        /* if no thread is available do mono-thread merge sort*/
        mergeSortParallel(array, arraySize / 2, bufferArray, threads, threadsNumber, myMutex);
        mergeSortParallel(array + arraySize / 2, arraySize - arraySize / 2, bufferArray + arraySize / 2, threads, threadsNumber, myMutex);
        merge(array, arraySize, bufferArray);
    }
}

int checkThreadIsAvailable(ThreadState* threads, int threadsNumber) {
    int index;
    for (index = 0; index < threadsNumber; index++)
    {
        if (threads[index].isUsed == False)
            return index;
    }
    return -1;
}

void* mergeSortParallelThread(void* input) {
    mergeSortParallel((*(MergeSortThreadArgs*)input).A, (*(MergeSortThreadArgs*)input).size, (*(MergeSortThreadArgs*)input).B, (*(MergeSortThreadArgs*)input).threads, (*(MergeSortThreadArgs*)input).threadsNumber, (*(MergeSortThreadArgs*)input).myMutex);
    pthread_exit(NULL);
}
