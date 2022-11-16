#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H

#define MAX_NUMBER_PRINT 100
#define COMPLETE_NUMBER_PRINT_THRESHOLD 1000

#include <stdlib.h>

void* allocateMemory(size_t size);

void printArray(const int* array, int begin, int size);

void printArraySummary(int* array, int arraySize);

int isSorted(const int* array, int arraySize);

void copyStreamToIntArray(int* array, int arraySize);

void randomizeIntArray(int* array, int arraySize, int minNumber, int maxNumber);

int randomInt(int minNumber, int maxNumber);

#endif
