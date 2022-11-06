#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

int main(int argc, char* argv[]) {
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

    fprintf(file, "%d\n", size);
    for (int i = 0; i < size; i++)
    {
        int random = rand() % INT_MAX;
        fprintf(file, "%d\n", random);
    }

    fclose(file);
    return 0;
}
