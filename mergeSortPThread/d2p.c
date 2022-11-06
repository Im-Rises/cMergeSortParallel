#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct MergeSortArgs MergeSortArgs;

struct MergeSortArgs {
    int* A;
    int p;
    int r;
    int* B;
    int s;
};

typedef struct MergeArgs MergeArgs;

struct MergeArgs {
    int* T;
    int p1;
    int r1;
    int p2;
    int r2;
    int* A;
    int p3;
};


void parallelMergeSort(int A[], int p, int r, int B[], int s);

void* parallelMergeSortThread(void* input);

void parallelMerge(int T[], int p1, int r1, int p2, int r2, int A[], int p3);

void* parallelMergeThread(void* input);

int binarySearch(int x, int T[], int p, int r);

void printArray(char* text, const int* array, const int size);

void swap(int* a, int* b);

int main() {
    int inputArray[] = { 10, 2, 3, 30, 432, 1, -52, 100, 0, 5 };
    int outputArray[10];

    int arraySize = (sizeof(inputArray) / sizeof(int));

    printArray("Array not sorted: ", inputArray, arraySize);

    parallelMergeSort(inputArray, 0, arraySize - 1, outputArray, 0);

    printArray("Array sorted: ", outputArray, arraySize);

    return 0;
}

void parallelMergeSort(int A[], int p, int r, int B[], int s) {
    int n = r - p + 1;
    if (n == 1)
        B[s] = A[p];
    else
    {
        int T[n];

        int q = (p + r) / 2;
        int q2 = q - p + 1;

        pthread_t thread_id;
        MergeSortArgs mergeSortArgs;
        mergeSortArgs.A = A;
        mergeSortArgs.p = p;
        mergeSortArgs.r = q;
        mergeSortArgs.B = T;
        mergeSortArgs.s = 0;

        pthread_create(&thread_id, NULL, parallelMergeSortThread, (void*)&mergeSortArgs);

        parallelMergeSort(A, q + 1, r, T, q2);

        pthread_join(thread_id, NULL);

        parallelMerge(T, 0, q2 - 1, q2, n - 1, B, s);
    }
}

void* parallelMergeSortThread(void* input) {
    parallelMergeSort((*(MergeSortArgs*)input).A, (*(MergeSortArgs*)input).p, (*(MergeSortArgs*)input).r,
        (*(MergeSortArgs*)input).B, (*(MergeSortArgs*)input).s);
    pthread_exit(NULL);
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

        pthread_t thread_id;
        MergeArgs mergeArgs;
        mergeArgs.T = T;
        mergeArgs.p1 = p1;
        mergeArgs.r1 = q1-1;
        mergeArgs.p2 = p2;
        mergeArgs.r2 = q2 - 1;
        mergeArgs.A = A;
        mergeArgs.p3 = p3;
        pthread_create(&thread_id, NULL, parallelMergeThread, (void*)&mergeArgs);

        parallelMerge(T, q1 + 1, r1, q2, r2, A, q3 + 1);

        pthread_join(thread_id, NULL);
    }
}

void* parallelMergeThread(void* input) {
    parallelMerge((*(MergeArgs*)input).T, (*(MergeArgs*)input).p1, (*(MergeArgs*)input).r1, (*(MergeArgs*)input).p2, (*(MergeArgs*)input).r2, (*(MergeArgs*)input).A, (*(MergeArgs*)input).p3);
    pthread_exit(NULL);
}

int binarySearch(int x, int T[], int p, int r) {
    int low = p;
    int high = p > r + 1 ? p : r + 1;
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

void printArray(char* text, const int* array, const int size) {
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
