#include "mergeSortParallelOpenMp.h"

#include <stdio.h>
#include <omp.h>

#include "../mergeSortSequential/mergeSortSequential.h"
#include "../commonFunctions/commonFunctions.h"

void mergeSortParallel(int a[], int size, int temp[]);

void mergeSortParallelOpenMp(int a[], int size, int threadsNumber) {
    /* Handle and print the number of threads */
    omp_set_num_threads(threadsNumber);
    printf("Number of maximum thread: %d\n", omp_get_max_threads());
    printf("Using %d threads\n", omp_get_max_threads());

    int* tempArray = allocateMemory(size * sizeof(int));

#pragma omp parallel
#pragma omp single
    mergeSortParallel(a, size, tempArray);

    free(tempArray);
}

void mergeSortParallel(int a[], int size, int temp[]) {
    if (size < MULTITHREAD_THRESHOLD)
    {
        mergeSort(a, size, temp);
        return;
    }
#pragma omp task
    mergeSortParallel(a, size / 2, temp);

    mergeSortParallel(a + size / 2, size - size / 2, temp + size / 2);

#pragma omp taskwait
    merge(a, size, temp);
}
