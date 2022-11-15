#include "mergeSortParallelPThread.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "../mergeSortSequential/mergeSortSequential.h"


void mergeSortParallelPThread(int A[], int arraySize, int B[], int threadsNumber) {
    ThreadState threads[threadsNumber];
    int i;
    for (i = 0; i < threadsNumber; i++)
    {
        threads[i].isUsed = False;
    }

    pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;

    mergeSortParallel(A, arraySize, B, threads, threadsNumber, &myMutex);
}

static void mergeSortParallel(int A[], int arraySize, int B[], ThreadState* threads, int threadsNumber, pthread_mutex_t* myMutex) {
    /* if array is too small do mono-thread merge sort*/
    if (arraySize < MULTITHREAD_THRESHOLD)
    {
        mergeSort(A, arraySize, B);
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
        MergeSortArgs args = {
            A,
            arraySize / 2,
            B,
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
        mergeSortParallel(A + arraySize / 2, arraySize - arraySize / 2, B + arraySize / 2, threads, threadsNumber, myMutex);

        /* wait for the thread to finish*/
        pthread_join(threads[threadIndex].thread, NULL);

        /* Free the thread to use*/
        threads[threadIndex].isUsed = False;

        /* merge the two sorted arrays*/
        merge(A, arraySize, B);
    }
    else
    {
        /* if no thread is available do mono-thread merge sort*/
        mergeSortParallel(A, arraySize / 2, B, threads, threadsNumber, myMutex);
        mergeSortParallel(A + arraySize / 2, arraySize - arraySize / 2, B + arraySize / 2, threads, threadsNumber, myMutex);
        merge(A, arraySize, B);
    }
}

static int checkThreadIsAvailable(ThreadState* threads, int threadsNumber) {
    int index;
    for (index = 0; index < threadsNumber; index++)
    {
        if (threads[index].isUsed == False)
            return index;
    }
    return -1;
}

static void* mergeSortParallelThread(void* input) {
    mergeSortParallelPthread((*(MergeSortArgs*)input).A, (*(MergeSortArgs*)input).size, (*(MergeSortArgs*)input).B, (*(MergeSortArgs*)input).threads, (*(MergeSortArgs*)input).threadsNumber, (*(MergeSortArgs*)input).myMutex);
    pthread_exit(NULL);
}