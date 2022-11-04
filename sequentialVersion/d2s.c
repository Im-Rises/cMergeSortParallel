#include <stdio.h>

#define ARRAY_SIZE 3

void printArray(int* array, int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void merge(int arr[], int aux[], int low, int mid, int high) {
    int k = low, i = low, j = mid + 1;

    while (i <= mid && j <= high)
    {
        if (arr[i] <= arr[j])
            aux[k++] = arr[i++];
        else
            aux[k++] = arr[j++];
    }

    while (i <= mid)
    {
        aux[k++] = arr[i++];
    }
    for (int i = low; i <= high; i++)
        arr[i] = aux[i];
}

void mergeSort(int arr[], int aux[], int low, int high) {
    if (high == low)
        return;

    int mid = (low + ((high - low) >> 1));
    mergeSort(arr, aux, low, mid);
    mergeSort(arr, aux, mid + 1, high);
    merge(arr, aux, low, mid, high);
}


int main() {
    int array[ARRAY_SIZE] = { 10, 2, 3 };
    int sortedArray[ARRAY_SIZE];

    printArray(array, ARRAY_SIZE);

    mergeSort(array, sortedArray, 0, ARRAY_SIZE - 1);

    printArray(array, ARRAY_SIZE);

    return 0;
}
