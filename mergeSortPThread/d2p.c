#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#ifdef _OPENMP
#include <omp.h>
#endif

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
void swap(int* a, int* b);

void* allocateMemory(size_t size);
void printArraySummary(int* array, int arraySize);
void printArray(const int* array, int begin, int size);


int main() {
    /*
     * Error list:
     * 1 - Wrong number of arguments
     * 2 - Error opening file
     * 3 - Error reading line from file
     * 4 - Error allocating memory
     */
    printf("-----Merge Sort Parallel using PThread-----\n\n");
    printf("To get elapsed time, compile with OpenMP's flag -fopenmp\n\n");

    /* Read size of array from stream */
    int arraySize = 0;
    scanf("%d", &arraySize);
    printf("Array size: %d\n", arraySize);

    /* Create array */
    int* inputArray = allocateMemory(arraySize * sizeof(int));
    int* outputArray = allocateMemory(arraySize * sizeof(int));

    /* Copy data from stream to array */
    int i;
    for (i = 0; i < arraySize; i++)
    {
        if (scanf("%d", &inputArray[i]) != 1)
        {
            printf("Error reading line from stream");
            return 3;
        }
    }

#if defined(_OPENMP)
    /* Create timer */
    double start = omp_get_wtime();
#endif

    /* Sort array */
    parallelMergeSort(inputArray, 0, arraySize - 1, outputArray, 0);

#if defined(_OPENMP)
    /* Stop timer */
    printf("Time elapsed: %lf seconds\n\n", omp_get_wtime() - start);
#endif

    /* Print array */
    printArraySummary(outputArray, arraySize);

    /* free memory */
    free(inputArray);
    free(outputArray);

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

        int threadCode = pthread_create(&thread_id, NULL, parallelMergeSortThread, (void*)&mergeSortArgs);
        if (threadCode == 0)
        {
            parallelMergeSort(A, q + 1, r, T, q2);
            pthread_join(thread_id, NULL);
        }
        else
        {
            parallelMergeSort(A, p, q, T, 0);
            parallelMergeSort(A, q + 1, r, T, q2);
        }

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
        mergeArgs.r1 = q1 - 1;
        mergeArgs.p2 = p2;
        mergeArgs.r2 = q2 - 1;
        mergeArgs.A = A;
        mergeArgs.p3 = p3;
        int threadCode = pthread_create(&thread_id, NULL, parallelMergeThread, (void*)&mergeArgs);
        if (threadCode == 0)
        {
            parallelMerge(T, q1 + 1, r1, q2, r2, A, q3 + 1);
            pthread_join(thread_id, NULL);
        }
        else
        {
            parallelMerge(T, p1, q1 - 1, p2, q2 - 1, A, p3);
            parallelMerge(T, q1 + 1, r1, q2, r2, A, q3 + 1);
        }
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

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void* allocateMemory(size_t size) {
    void* memory = malloc(size);
    if (memory == NULL)
    {
        printf("Error allocating memory");
        exit(4);
    }
    return memory;
}

void printArraySummary(int* array, int arraySize) {
    printf("Array sorted:\n");
    if (arraySize > 1000)
    {
        printf("Array too big to print\n");
        printf("- First 100 values: \n");
        printArray(array, 0, 100);
        printf("...\n");
        printf("- Last 100 values: \n");
        printArray(array, arraySize - 100, arraySize);
    }
    else
    {
        printArray(array, 0, arraySize);
    }
}

void printArray(const int* array, const int begin, const int size) {
    int i;
    for (i = begin; i < size; i++)
        printf("%d\n", array[i]);
    printf("\n");
}
