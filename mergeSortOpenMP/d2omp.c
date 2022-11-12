#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define INIT_THREADS_NUMBER 4

#define MAX_NUMBER_PRINT 100
#define COMPLETE_NUMBER_PRINT_THRESHOLD 1000

#define MULTITHREAD_THRESHOLD 1000

void mergeSortParallel(int A[], int left, int right, int* B);
void mergeSort(int A[], int left, int right, int* B);
void merge(int A[], int left, int mid, int right, int* B);

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
    printf("- Array size: %d\n", arraySize);

    /* Create array */
    int* inputArray = allocateMemory(arraySize * sizeof(int));
    int* outputArray = allocateMemory(arraySize * sizeof(int));

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

    mergeSortParallel(inputArray, 0, arraySize - 1, outputArray);

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
    printf("Is array correctly sorted? %s\n", isSorted(outputArray, arraySize) ? "No" : "Yes");

    /* Print array */
    printArraySummary(outputArray, arraySize);

    /* Free memory */
    free(inputArray);
    free(outputArray);

    return 0;
}

void mergeSortParallel(int A[], int left, int right, int* B) {
    if (left < right)
    {
        if (right - left < MULTITHREAD_THRESHOLD)
        {
            mergeSort(A, left, right, B);
        }
        else
        {
            int mid = (left + right) / 2;

#pragma omp parallel
            {
#pragma omp single
                {
#pragma omp task
                    mergeSortParallel(A, left, mid, B);
#pragma omp task
                    mergeSortParallel(A, mid + 1, right, B);
#pragma omp taskwait
                    merge(A, left, mid, right, B);
                }
            }
        }
    }
}


void mergeSort(int A[], int left, int right, int* B) {
    if (left < right)
    {
        int mid = (left + right) / 2;
        mergeSort(A, left, mid, B);
        mergeSort(A, mid + 1, right, B);
        merge(A, left, mid, right, B);
    }
}

void merge(int A[], int left, int mid, int right, int* B) {

    int i = left,
        j = mid + 1,
        k = 0;

    int Ai = A[i];
    int Aj = A[j];

    while (i <= mid && j <= right)
    {
        if (Ai <= Aj)
        {
            B[k++] = Ai;
            Ai = A[++i];
        }
        else
        {
            B[k++] = Aj;
            Aj = A[++j];
        }
    }

    while (i <= mid)
        B[k++] = A[i++];

    while (j <= right)
        B[k++] = A[j++];

    for (i = left; i <= right; ++i)
        A[i] = B[i - left];
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
