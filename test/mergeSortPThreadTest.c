#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#include "../commonFunctions/commonFunctions.h"
#include "../mergeSortPThread/mergeSortParallelPThread.h"

int main() {
#ifdef _WIN32
    printf("Windows platform cannot be tested with PThread, use Linux instead.\n");
#elif __unix__

#endif

    return 0;
}
