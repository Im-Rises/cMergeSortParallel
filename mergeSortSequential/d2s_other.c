#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#if defined(_OPENMP)
#include <omp.h>
#endif

 void mergeSort(int A[], int p, int r);
 void merge(int A[], int p, int q, int r);
 void* allocateMemory(size_t size);
 void printArraySummary(int* array, int arraySize);
 void printArray(const int* array, int begin, int size);

 int main(int argc, char* argv[]) {
    /*
     * Error list:
     * 1 - Wrong number of arguments
     * 2 - Error opening file
     * 3 - Error reading line from file
     * 4 - Error allocating memory
     */
    printf("-----Merge Sort Sequential-----\n\n");
    printf("To get elapsed time, compile with OpenMP's flag -fopenmp\n\n");

    /* Read size of array from stream */
    int arraySize = 0;
    scanf("%d", &arraySize);
    printf("Array size: %d\n", arraySize);

    /* Create array */
    int* array = allocateMemory(arraySize * sizeof(int));

    /* Copy data from stream to array */
    int i;
    for (i = 0; i < arraySize; i++)
    {
        if (scanf("%d", &array[i]) != 1)
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
    mergeSort(array, 0, arraySize - 1);

#if defined(_OPENMP)
    /* Stop timer */
    printf("Time elapsed: %lf seconds\n\n", omp_get_wtime() - start);
#endif

    /* Print array */
    printArraySummary(array, arraySize);

    /* free memory */
    free(array);

    return 0;
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

    int i,j;
    for (i = 0; i < n1; i++)
        L[i] = A[p + i];
    for (j = 0; j < n2; j++)
        R[j] = A[q + j + 1];
    L[n1] = INT_MAX;
    R[n2] = INT_MAX;
    i = 0;
    j = 0;
    int k;
    for (k = p; k <= r; k++)
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
}



 void* allocateMemory(size_t size)
{
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
