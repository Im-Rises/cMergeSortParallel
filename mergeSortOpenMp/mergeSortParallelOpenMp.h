#ifndef MERGE_SORT_PARALLEL_OPENMP_H
#define MERGE_SORT_PARALLEL_OPENMP_H

#define MULTITHREAD_THRESHOLD 1000

void mergeSortParallelOpenMp(int array[], int size, int threadsNumber);

#endif
