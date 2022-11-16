#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#include "../commonFunctions/commonFunctions.h"
#include "../mergeSortSequential/mergeSortSequential.h"

int main() {
    int n = 1000000;
    int* A = allocateMemory(n * sizeof(int));

    srand(time(NULL));

    randomizeIntArray(A, n, 0, INT_MAX);

    mergeSortSequential(A, n);

    int errorCode = isSorted(A, n);

    if (errorCode == 0)
        printf("- mergeSortSequential ok!\n");
    else
        printf("- mergeSortSequential fail!\n");

    free(A);
    return errorCode;
}
