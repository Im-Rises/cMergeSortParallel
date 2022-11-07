#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define MAX_THREADS 4

void mergeSortParallel(int A[], int p, int r);
void mergeSort(int A[], int p, int r);
void merge(int A[], int p, int q, int r);

void* allocateMemory(size_t size);
void printArraySummary(int* array, int arraySize);
void printArray(const int* array, int begin, int size);

/* void swap(int* a, int* b);
 int binarySearch(int x, int T[], int p, int r);
 void parallelMerge(int T[], int p1, int r1, int p2, int r2, int A[], int p3);
 void parallelMergeSort(int A[], int p, int r, int B[], int s);*/

int main() {
    /*
     * Error list:
     * 1 - Wrong number of arguments
     * 2 - Error opening file
     * 3 - Error reading line from file
     * 4 - Error allocating memory
     */
    printf("-----Merge Sort Parallel using OpenMP-----\n\n");

    /* Read size of array from stream */
    int arraySize = 0;
    scanf("%d", &arraySize);
    printf("Array size: %d\n", arraySize);

    /* Create array */
    int* inputArray = allocateMemory(arraySize * sizeof(int));

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

    /* Print the number of threads */
    /*        omp_set_num_threads(MAX_THREADS);
        omp_set_num_threads(omp_get_max_threads());*/
    printf("Number of threads: %d\n", omp_get_max_threads());

    clock_t clockTimer;
    clockTimer = clock();
    printf("Merge sort timer starts\n");

    mergeSortParallel(inputArray, 0, arraySize - 1);

    clockTimer = clock() - clockTimer;
    double time_taken = ((double)clockTimer) / CLOCKS_PER_SEC; /*calculate the elapsed time*/
    printf("The merge sort took %f seconds to execute\n", time_taken);

    /* Print array */
    printArraySummary(inputArray, arraySize);

    free(inputArray);

    return 0;
}

void mergeSortParallel(int A[], int p, int r) {
    if (p < r)
    {
        int q = (p + r) / 2;

#pragma omp task shared(A)
        mergeSort(A, p, q);
#pragma omp task shared(A)
        mergeSort(A, q + 1, r);
#pragma omp taskwait
        merge(A, p, q, r);
    }
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

void merge(int A[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;

    int L[n1 + 1];
    int R[n2 + 1];

    int i, j, k;

    for (i = 0; i < n1; i++)
        L[i] = A[p + i];
    for (j = 0; j < n2; j++)
        R[j] = A[q + j + 1];

    L[n1] = INT_MAX;
    R[n2] = INT_MAX;

    i = 0;
    j = 0;
    for (k = p; k <= r; k++)
    {
        if (L[i] <= R[j])
        {
            A[k] = L[i];
            i++;
        }
        else
        {
            A[k] = R[j];
            j++;
        }
    }
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


/*--------------OTHER MERGE SORT FUNCTIONS--------------*/
/*
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
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
        */
/*#pragma omp parallel sections
      {
#pragma omp section*/
/*
parallelMerge(T, p1, q1 - 1, p2, q2 - 1, A, p3);
*/
/*#pragma omp section*/ /*
           parallelMerge(T, q1 + 1, r1, q2, r2, A, q3 + 1);
       */
/*}*/                   /*
             }
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
         #pragma omp parallel sections
                 {
         #pragma omp section
                     parallelMergeSort(A, p, q, T, 0);
         #pragma omp section
                     parallelMergeSort(A, q + 1, r, T, q2);
                 }
                 parallelMerge(T, 0, q2 - 1, q2, n - 1, B, s);
             }
         }*/
