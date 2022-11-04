#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ARRAY_SIZE 3

void printArray(int* array, int size) {
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void merge(int U[], int V[], int T[], int n) {
    int i = 0;
    int j = 0;
    U[n / 2] = INT_MAX;
    V[n / 2] = INT_MAX;
    for (int k = 0; k < n; k++)
    {
        if (U[i] < V[j])
        {
            T[k] = U[i++];
        }
        else
        {
            T[k] = V[j++];
        }
    }
}

void mergeSort(int T[], int n) {
    if (n <= 1)
    {
        return;
    }

    int* U = malloc(((n / 2) + 1) * sizeof(int));
    int* V = malloc(((n / 2) + 1) * sizeof(int));
    if (U == NULL || V == NULL)
    {
        printf("Memory allocation error!");
        exit(1);
    }


    for (int i = 0; i < n / 2; i++)
    {
        U[i] = T[i];
        V[i] = T[i + n / 2];
    }

    mergeSort(U, n / 2);
    mergeSort(V, n / 2);
    merge(U, V, T, n);

    free(U);
    free(V);
}

int main() {
    int array[ARRAY_SIZE] = { 10, 2, 3 };

    printArray(array, ARRAY_SIZE);

    mergeSort(array, ARRAY_SIZE);

    printArray(array, ARRAY_SIZE);

    return 0;
}
