#ifndef MERGE_SORT_PARALLEL_OPENMP_H
#define MERGE_SORT_PARALLEL_OPENMP_H

#define MULTITHREAD_THRESHOLD 1000

void mergeSortParallelOpenMp(int a[], int size, int temp[], int threadsNumber);

#endif
