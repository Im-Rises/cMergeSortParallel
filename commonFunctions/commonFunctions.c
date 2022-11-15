#include "commonFunctions.h"

#include <stdio.h>


void* allocateMemory(size_t size) {
    void* memory = malloc(size);
    if (memory == NULL)
    {
        fprintf(stderr, "Error allocating memory");
        exit(2);
    }
    return memory;
}

void printArray(const int* array, const int begin, const int size) {
    int i;
    for (i = begin; i < size; i++)
        printf("%d\n", array[i]);
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

void copyStreamToIntArray(int* array, int arraySize) {
    int i;
    for (i = 0; i < arraySize; i++)
    {
        if (scanf("%d", &array[i]) != 1)
        {
            fprintf(stderr, "Error reading line from stream");
            exit(1);
        }
    }
}

void randomizeIntArray(int* array, int arraySize, int minNumber, int maxNumber) {
    int i;
    for (i = 0; i < arraySize; i++)
    {
        array[i] = randomInt(minNumber, maxNumber);
    }
}

int randomInt(int minNumber, int maxNumber) {
    return rand() % (maxNumber - minNumber + 1) + minNumber;
}
