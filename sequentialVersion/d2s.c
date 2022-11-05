#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void printArray(char* text, const int* array, const int size) {
    printf("%s", text);
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void merge(int A[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
#ifdef _WIN32
    int* L = (int*)malloc((n1 + 1) * sizeof(int));
    int* R = (int*)malloc((n2 + 1) * sizeof(int));
#elif defined(__unix__)
    int L[n1 + 1];
    int R[n2 + 1];
#else
#warning "Not implemented for macOs"
#endif
    for (int i = 0; i < n1; i++)
        L[i] = A[p + i];
    for (int j = 0; j < n2; j++)
        R[j] = A[q + j + 1];
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    int i = 0;
    int j = 0;
    for (int k = p; k <= r; k++)
    {
        if (L[i] <= R[j])
        {
            A[k] = L[i];
            i = i + 1;
        }
        else
        {
            A[k] = R[j];
            j = j + 1;
        }
    }
#ifdef _WIN32
    free(L);
    free(R);
#endif
}

void mergeSort(int A[], int p, int r) {
    if (p < r)
    {
        int q = (p + r) / 2;
        mergeSort(A, p, q);
        mergeSort(A, q + 1, r);
        merge(A, p, q, r);
    }
}


int main() {
    int array[] = { 10, 2, 3, 30, 432, 1, -52, 100, 0, 5 };

    int arraySize = (sizeof(array) / sizeof(int));

    printArray("Array not sorted: ", array, arraySize);

    mergeSort(array, 0, arraySize - 1);

    printArray("Array sorted: ", array, arraySize);

    return 0;
}
