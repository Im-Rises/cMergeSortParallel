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

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int binarySearch(int* arr, int x, int l, int h) {
    if (l > h)
        return -1;
    else
    {
        int mid = (l + h) / 2;
        if (arr[mid] == x)
            return mid;
        else if (arr[mid] > x)
            return binarySearch(arr, x, l, mid - 1);
        else
            return binarySearch(arr, x, mid + 1, h);
    }
}

void merge(int T[], int p1, int r1, int p2, int r2, int A[], int p3) {
    int n1 = r1 - p1 + 1;
    int n2 = r2 - p2 + 1;
    if (n1 < n2)
    {
        swap(&n1, &n2);
        swap(&p1, &p2);
        swap(&r1, &r2);
    }
    else
    {
        int q1 = (p1 + r1) / 2;
        int q2 = binarySearch(T, T[q1], p2, r2);
        int q3 = p3 + (q1 - p1) + (q2 - p2);
        A[q3] = T[q1];
        merge(T, p1, q1 - 1, p2, q2 - 1, A, p3);
        merge(T, q1 + 1, r1, q2, r2, A, q3 + 1);
    }
}

void mergeSort(int A[], int p, int r) {
    if (p >= r)
        return;
    int q = (p + r) / 2;
    mergeSort(A, p, q);
    mergeSort(A, q + 1, r);
    merge(A, p, q, q + 1, r, A, p);
}

int main() {
    int array[ARRAY_SIZE] = { 10, 2, 3 };

    printArray(array, ARRAY_SIZE);

    mergeSort(array, 0, ARRAY_SIZE);

    printArray(array, ARRAY_SIZE);

    return 0;
}
