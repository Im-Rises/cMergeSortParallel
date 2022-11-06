#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#if defined(_OPENMP)
#include <omp.h>
#endif

void mergeSort(int A[], int p, int r);

void merge(int A[], int p, int q, int r);

FILE* openFile(char* fileName, char* mode);

void readLine(FILE* file, int* value);

void* allocateMemory(size_t size);

void copyArrayFromFileToArray(FILE* file,int* array, int arraySize);

void printArraySummary(int* array, int arraySize);

void printArray(const int* array, int begin, int size);

void copyArrayToFile(FILE* file, int* array, int arraySize);

int main(int argc, char* argv[]) {
    /*
     * Error list:
     * 1 - Wrong number of arguments
     * 2 - Error opening file
     * 3 - Error reading line from file
     * 4 - Error allocating memory
     */

    printf("-----Merge Sort Sequential-----\n\n");
    if (argc != 3)
    {
        printf("Merge Sort Sequential version: Usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }

    char* inputFileName = argv[1];
    char* outputFileName = argv[2];

    // Open input file
    FILE* inputFile = openFile(inputFileName, "r");

    // Read size of array
    int arraySize = 0;
    readLine(inputFile, &arraySize);
    printf("Array size: %d\n", arraySize);

    // Create array
    int* array = allocateMemory(arraySize * sizeof(int));

    // Copy data from input file to array
    copyArrayFromFileToArray(inputFile, array, arraySize);

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
    printArraySummary(array, arraySize);

    // Create output file
    FILE* file = openFile(outputFileName, "w");

    // Write output file
    copyArrayToFile(file, array, arraySize);

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

FILE* openFile(char* fileName, char* mode){
    FILE* file = fopen(fileName, mode);
    if (file == NULL)
    {
        printf("Error opening file: %s", fileName);
        exit(2);
    }
    return file;
}

void readLine(FILE* file, int* value)
{
    if (fscanf(file, "%d", value) != 1)
    {
        printf("Error reading file");
        exit(3);
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

void copyArrayFromFileToArray(FILE* file,int* array, int arraySize)
{
    for (int i = 0; i < arraySize; i++)
    {
        fscanf(file, "%d", &array[i]);
    }
}

void printArraySummary(int* array, int arraySize) {
    if (arraySize > 1000)
    {
        printf("Array too big to print\n");
        printf("First 100 values: \n");
        printArray(array, 0, 100);
        printf("...\n");
        printf("Last 100 values: \n");
        printArray(array, arraySize - 100, arraySize);
    }
    else
    {
        printf("Array sorted: \n");
        printArray(array, 0, arraySize);
    }
}

void printArray(const int* array, const int begin, const int size) {
    for (int i = begin; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void copyArrayToFile(FILE* file, int* array, int arraySize){
    for (int i = 0; i < arraySize; i++)
    {
        fprintf(file, "%d\n", array[i]);
    }
}
