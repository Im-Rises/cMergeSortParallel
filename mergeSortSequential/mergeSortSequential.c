#include "mergeSortSequential.h"

#include <string.h>

void mergeSort(int* X, int n, int* tmp) {
    if (n < 2)
        return;
    mergeSort(X, n / 2, tmp);
    mergeSort(X + n / 2, n - n / 2, tmp);
    merge(X, n, tmp);
}

static void merge(int* X, int n, int* tmp) {
    int i = 0;
    int j = n / 2;
    int k = 0;

    while (i < n / 2 && j < n)
    {
        if (X[i] < X[j])
        {
            tmp[k] = X[i];
            k++;
            i++;
        }
        else
        {
            tmp[k] = X[j];
            k++;
            j++;
        }
    }
    while (i < n / 2)
    {
        tmp[k] = X[i];
        k++;
        i++;
    }
    while (j < n)
    {
        tmp[k] = X[j];
        k++;
        j++;
    }
    memcpy(X, tmp, n * sizeof(int));
}
