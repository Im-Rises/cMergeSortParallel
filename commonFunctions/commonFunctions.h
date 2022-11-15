#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H

#define MAX_NUMBER_PRINT 100
#define COMPLETE_NUMBER_PRINT_THRESHOLD 1000

void* allocateMemory(size_t size);

void printArray(const int* array, int begin, int size);

void printArraySummary(int* array, int arraySize);

int isSorted(const int* array, int arraySize);

void copyStreamToIntArray(int* array, int arraySize);

#endif

//
// void myTimeTest() {
//    /* Create timer */
//    clock_t clockTimer;
//    clockTimer = clock();
//#ifdef _OPENMP
//    double openMpT = omp_get_wtime();
//#endif
//#ifdef __unix__
//    struct timespec timeSpecStart, timeSpecFinish;
//    double unixTimelapsed;
//    clock_gettime(CLOCK_MONOTONIC, &timeSpecStart);
//#endif
//
//
//    /* Stop timer */
//    clockTimer = clock() - clockTimer;
//    double time_taken = ((double)clockTimer) / CLOCKS_PER_SEC; /*calculate the elapsed time*/
//#ifdef _OPENMP
//    double openMpTime = (omp_get_wtime() - openMpT);
//#endif
//#ifdef __unix__
//    clock_gettime(CLOCK_MONOTONIC, &timeSpecFinish);
//    unixTimelapsed = (timeSpecFinish.tv_sec - timeSpecStart.tv_sec);
//    unixTimelapsed += (timeSpecFinish.tv_nsec - timeSpecStart.tv_nsec) / 1000000000.0;
//#endif
//
//    /* Print results */
//    printf("Time elapsed:\n");
//    printf(" - Standard Timer: %f s\n", time_taken);
//#ifdef _OPENMP
//    printf(" - OpenMP Timer: %f s\n", openMpTime);
//#endif
//#ifdef __unix__
//    printf(" - Unix Timer: %f s\n", unixTimelapsed);
//#endif
//}
//
//#endif
