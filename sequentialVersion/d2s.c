#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#if defined(_OPENMP)
#include <omp.h>
#endif

void mergeSort(int A[], int p, int r);

void merge(int A[], int p, int q, int r);

void printArray(const int* array, int begin, int size);

int main(int argc, char* argv[]) {
    if (argc != 3)
    {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }

    char* inputFileName = argv[1];
    char* outputFileName = argv[2];

    // Open input file
    FILE* inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL)
    {
        printf("Error opening input file");
        return 2;
    }
    // Read size of array
    int arraySize = 0;
    fscanf(inputFile, "%d", &arraySize);
    printf("Array size: %d\n", arraySize);

    // Create array
    int* array = (int*)malloc(arraySize * sizeof(int));
    if (array == NULL)
    {
        printf("Error allocating memory");
        return 2;
    }

    // Read input file
    for (int i = 0; i < arraySize; i++)
    {
        fscanf(inputFile, "%d", &array[i]);
    }

    // Close input file
    fclose(inputFile);

#if defined(_OPENMP)
// Create timer
    double start = omp_get_wtime();
#endif

    // Sort array
    mergeSort(array, 0, arraySize - 1);

#if defined(_OPENMP)
    // Stop timer
    double end = omp_get_wtime();
    printf("Sort and merge Sequential\n"
           "Time elapsed: %lf seconds\n"
        , end - start);
#endif

    // Print array
    if (arraySize > 1000)
    {
        printf("Array too big to print\n");
        printf("First 100 values: \n");
        printArray(array, 0, 100);
        printf("...\n");
        printf("Last 100 values: \n");
        printArray(array, arraySize - 100, arraySize);
        printf("...\n");
    }
    else
    {
        printf("Array sorted: \n");
        printArray(array, 0, arraySize);
    }

    // Create output file
    FILE* file = fopen(outputFileName, "w");
    if (file == NULL)
    {
        printf("Error opening file");
        return 3;
    }

    // Write output file
    for (int i = 0; i < arraySize; i++)
    {
        fprintf(file, "%d\n", array[i]);
    }

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
}

void printArray(const int* array, const int begin, const int size) {
    for (int i = begin; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}
