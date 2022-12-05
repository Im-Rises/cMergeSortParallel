#include "mergeSortSequential.h"
#include "../commonFunctions/commonFunctions.h"

#include <string.h>

void mergeSortSequential(int* array, int arraySize) {
    int* bufferArray = allocateMemory(arraySize * sizeof(int));
    mergeSort(array, arraySize, bufferArray);
    free(bufferArray);
}

void mergeSort(int* array, int n, int* bufferArray) {
    if (n < 2)
        return;
    mergeSort(array, n / 2, bufferArray);
    mergeSort(array + n / 2, n - n / 2, bufferArray);
    merge(array, n, bufferArray);
}

void merge(int* array, int n, int* bufferArray) {
    int i = 0;
    int j = n / 2;
    int k = 0;

    while (i < n / 2 && j < n)
    {
        if (array[i] < array[j])
        {
            bufferArray[k] = array[i];
            k++;
            i++;
        }
        else
        {
            bufferArray[k] = array[j];
            k++;
            j++;
        }
    }
    while (i < n / 2)
    {
        bufferArray[k] = array[i];
        k++;
        i++;
    }
    while (j < n)
    {
        bufferArray[k] = array[j];
        k++;
        j++;
    }
    memcpy(array, bufferArray, n * sizeof(int));
}
