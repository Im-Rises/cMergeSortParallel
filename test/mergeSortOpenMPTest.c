#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#include "../commonFunctions/commonFunctions.h"
#include "../mergeSortOpenMp/mergeSortParallelOpenMp.h"

int main() {
    int threadsNumber = 4;
    int n = 1000000;
    int* A = allocateMemory(n*sizeof(int));
    int* tmp = allocateMemory(n*sizeof(int));

    srand(time(NULL));

    randomizeIntArray(A, n, 0, INT_MAX);

    mergeSortParallelOpenMp(A, n, tmp, threadsNumber);

    int errorCode = isSorted(A, n);

    if (errorCode == 0)
        printf("- mergeSortParallelOpenMp ok!\n");
    else
        printf("- mergeSortParallelOpenMp fail!\n");

    free(A);
    free(tmp);
    return errorCode;
}

