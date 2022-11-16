#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "../commonFunctions/commonFunctions.h"

int main(int argc, char* argv[]) {
    /*
     * Error list:
     * 1 - Wrong number of arguments
     * 2 - Error opening file
     */

    printf("-----Random Array File Generator-----\n");
    if (argc != 3)
    {
        printf("Usage: %s <arraySize> <outputFile>\n", argv[0]);
        return 1;
    }

    /* Init input variables */
    char* fileName = argv[2];
    int size = atoi(argv[1]);

    /* Set random seed*/
    srand(time(NULL));


    /* Open file*/
    FILE* file = fopen(fileName, "w");
    if (file == NULL)
    {
        printf("Error opening file");
        return 2;
    }

    /* Create random value and write them in the output file*/
    fprintf(file, "%d\n", size);
    int minNumber = 0;
    int maxNumber = INT_MAX;
    int i;
    for (i = 0; i < size; i++)
    {
        int random = rand() % (maxNumber - minNumber + 1) + minNumber;
        fprintf(file, "%d\n", random);
    }

    fclose(file);

    printf("Array generated successfully\n");
    return 0;
}
