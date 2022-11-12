#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define INIT_THREADS_NUMBER 4

#define MAX_NUMBER_PRINT 100
#define COMPLETE_NUMBER_PRINT_THRESHOLD 1000

void mergeSortParallel(int A[], int p, int r);
void mergeSort(int A[], int p, int r);
void merge(int A[], int p, int q, int r);

void* allocateMemory(size_t size);
void printArraySummary(int* array, int arraySize);
void printArray(const int* array, int begin, int size);
int isSorted(const int* array, int arraySize);

int main(int argc, char* argv[]) {
    /*
     * Error list:
     * 1 - Error reading line from file
     * 2 - Error allocating memory
     */

    printf("|-----Merge Sort Parallel using OpenMP-----|\n\n");

    /* Read optional parameters */
    int threadsNumber = INIT_THREADS_NUMBER;
    if (argc != 1)
        threadsNumber = atoi(argv[1]);

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
            fprintf(stderr, "Error reading line from stream");
            return 1;
        }
    }

    /* Handle and print the number of threads */
    omp_set_num_threads(threadsNumber);
    /*omp_set_num_threads(omp_get_max_threads());*/
    /*printf("Using %d threads\n", omp_get_max_threads());*/
    printf("Number of threads: %d\n", omp_get_max_threads());

    /* Create timer */
    clock_t clockTimer;
    clockTimer = clock();
    double openMpT = omp_get_wtime();
#ifdef __unix__
    struct timespec timeSpecStart, timeSpecFinish;
    double unixTimelapsed;
    clock_gettime(CLOCK_MONOTONIC, &timeSpecStart);
#endif

    /* Sort array */
    mergeSortParallel(inputArray, 0, arraySize - 1);

    /* Stop timer */
    clockTimer = clock() - clockTimer;
    double time_taken = ((double)clockTimer) / CLOCKS_PER_SEC; /*calculate the elapsed time*/
    double openMpTime = (omp_get_wtime() - openMpT);
#ifdef __unix__
    clock_gettime(CLOCK_MONOTONIC, &timeSpecFinish);
    unixTimelapsed = (timeSpecFinish.tv_sec - timeSpecStart.tv_sec);
    unixTimelapsed += (timeSpecFinish.tv_nsec - timeSpecStart.tv_nsec) / 1000000000.0;
#endif

    /* Print results */
    printf("Time elapsed:\n");
    printf(" - Standard Timer: %f s\n", time_taken);
    printf(" - OpenMP Timer: %f s\n", openMpTime);
#ifdef __unix__
    printf(" - Unix Timer: %f s\n", unixTimelapsed);
#endif

    /* Print array is sorted */
    printf("Is array correctly sorted? %s\n", isSorted(inputArray, arraySize) ? "No" : "Yes");

    /* Print array */
    /*    printArraySummary(inputArray, arraySize);*/

    /* Free memory */
    free(inputArray);

    return 0;
}

void mergeSortParallel(int A[], int p, int r) {
    if (p < r)
    {
        int q = (p + r) / 2;

#pragma omp parallel sections
        {
#pragma omp section
            mergeSort(A, p, q);
#pragma omp section
            mergeSort(A, q + 1, r);
        }
        merge(A, p, q, r);

        /*#pragma omp task
                mergeSort(A, p, q);
        #pragma omp task
                mergeSort(A, q + 1, r);
        #pragma omp taskwait
                merge(A, p, q, r);*/
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
    int i, j, k;

    int n1 = q - p + 1;
    int n2 = r - q;

    int* L = allocateMemory((n1 + 1) * sizeof(int));
    int* R = allocateMemory((n2 + 1) * sizeof(int));
    /* int L[n1 + 1];
       int R[n2 + 1];*/

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
        fprintf(stderr, "Error allocating memory");
        exit(2);
    }
    return memory;
}

void printArraySummary(int* array, int arraySize) {
    printf("Array sorted: ");
    if (arraySize > COMPLETE_NUMBER_PRINT_THRESHOLD)
    {
        printf("(Array too big to be printed completely)\n");
        printf("- First %d values: \n", MAX_NUMBER_PRINT);
        printArray(array, 0, MAX_NUMBER_PRINT);
        printf("...\n");
        printf("- Last %d values: \n", MAX_NUMBER_PRINT);
        printArray(array, arraySize - MAX_NUMBER_PRINT, arraySize);
    }
    else
    {
        printf("\n");
        printArray(array, 0, arraySize);
    }
}

void printArray(const int* array, const int begin, const int size) {
    int i;
    for (i = begin; i < size; i++)
        printf("%d\n", array[i]);
}

int isSorted(const int* array, int arraySize) {
    int i;
    for (i = 0; i < arraySize - 1; i++)
    {
        if (array[i] > array[i + 1])
        {
            return 1;
        }
    }
    return 0;
}
