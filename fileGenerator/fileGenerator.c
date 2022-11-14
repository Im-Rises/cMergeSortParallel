#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int main(int argc, char* argv[]) {
    /*
     * Error list:
     * 1 - Wrong number of arguments
     * 2 - Error opening file
     */

    printf("-----Random Array File Generator-----\n");
    if (argc != 3)
    {
        printf("Usage: %s <size of array> <output file>\n", argv[0]);
        return 1;
    }

    srand(time(NULL));

    char* fileName = argv[2];
    int size = atoi(argv[1]);

    FILE* file = fopen(fileName, "w");
    if (file == NULL)
    {
        printf("Error opening file");
        return 2;
    }

    /*Method 1*/
    fprintf(file, "%d\n", size);
    int minNumber = 0;
    int i;
    for (i = 0; i < size; i++)
    {
        int random = rand() % (INT_MAX + 1 - minNumber) + minNumber;
        fprintf(file, "%d\n", random);
    }

    /*Method 2*/
    /*    int* arrayBuffer = malloc(size * sizeof(int));
        for (i = 0; i < size; i++)
        {
            int random = rand() % (INT_MAX + 1 - minNumber) + minNumber;
            arrayBuffer[i] = random;
        }
        fwrite(arrayBuffer, sizeof(int), size, file);*/

    fclose(file);

    printf("Array generated successfully\n");
    return 0;
}
