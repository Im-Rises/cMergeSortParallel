#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <omp.h>

void printArray(char* text, int* array, int size) {
    printf("%s", text);
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int binarySearch(int x, int T[], int p, int r) {
    int low = p;
    int high = max(p, r + 1);
    while (low < high)
    {
        int mid = (low + high) / 2;
        if (x <= T[mid])
            high = mid;
        else
            low = mid + 1;
    }
    return high;
}

void parallelMerge(int T[], int p1, int r1, int p2, int r2, int A[], int p3) {
    int n1 = r1 - p1 + 1;
    int n2 = r2 - p2 + 1;
    if (n1 < n2)
    {
        swap(&p1, &p2);
        swap(&r1, &r2);
        swap(&n1, &n2);
    }
    if (n1 == 0)
        return;
    else
    {
        int q1 = (p1 + r1) / 2;
        int q2 = binarySearch(T[q1], T, p2, r2);
        int q3 = p3 + (q1 - p1) + (q2 - p2);
        A[q3] = T[q1];
#pragma omp task
        parallelMerge(T, p1, q1 - 1, p2, q2 - 1, A, p3);
#pragma omp task
        parallelMerge(T, q1 + 1, r1, q2, r2, A, q3 + 1);
    }
}

void parallelMergeSort(int A[], int p, int r, int B[], int s) {
    int n = r - p + 1;
    if (n == 1)
        B[s] = A[p];
    else
    {
#ifdef _WIN32
        int* T = (int*)malloc(n * sizeof(int));
#elif defined(__unix__)
        int T[n];
#else
#warning "Not implemented for macOs"
#endif
        int q = (p + r) / 2;
        int q2 = q - p + 1;
#pragma omp task
        parallelMergeSort(A, p, q, T, 0);
#pragma omp task
        parallelMergeSort(A, q + 1, r, T, q2);
#pragma omp taskwait
        parallelMerge(T, 0, q2 - 1, q2, n - 1, B, s);

#ifdef _WIN32
        free(T);
#endif
    }
}

int main() {
    int array[] = { 10, 2, 3, 30, 432, 1, -52, 100, 0, 5 };
    int otherArray[] = { 10, 2, 3, 30, 432, 1, -52, 100, 0, 5 };

    int arraySize = (sizeof(array) / sizeof(int));

    printArray("Array not sorted: ", array, arraySize);

    parallelMergeSort(array, 0, arraySize - 1, otherArray, 0);

    printArray("Array sorted: ", otherArray, arraySize);

    return 0;
}
