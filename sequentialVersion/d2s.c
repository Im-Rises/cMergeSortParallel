#include <stdio.h>
#include <stdlib.h>

void printArray(int* array, int size) {
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
}

void merge(int U[], int V[], int T[], int n) {
    int i = 0;
    int j = 0;
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

void mergeSort(int T[], int n, int U[], int V[]) {
    if (n <= 1)
    {
        return;
    }

    for (int i = 0; i < n / 2; i++)
    {
        U[i] = T[i];
        V[i] = T[i + n / 2];
    }

    //    mergeSort(U, n / 2, U, V);
    //    mergeSort(V, n / 2, U, V);
    //    merge(U, V, T, n);
}

#define ARRAY_SIZE 10

int main() {
    int array[ARRAY_SIZE] = { 10, 2, 3, 40, 5, 6, 70, 8, 9, 10 };
    int* U = malloc(ARRAY_SIZE * sizeof(int));
    int* V = malloc(ARRAY_SIZE * sizeof(int));

    mergeSort(array, ARRAY_SIZE, U, V);

    free(U);
    free(V);

    printArray(array, ARRAY_SIZE);

    return 0;
}
