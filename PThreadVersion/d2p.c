#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void printArray(char* text, int* array, int size) {
    printf("%s", text);
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int binarySearch(int x, int T[], int p, int r) {
    int low = p;
    //    int high = max(p, r + 1);
    int high = p > r + 1 ? p : r + 1;
    while (low < high)
    {
        int mid = (low + high) / 2;
        if (x <= T[mid])
            high = mid;
        else
            low = mid + 1;
    }
    return high;
}

void* myThreadFun(void* vargp) {
    sleep(1);
    printf("Printing GeeksQuiz from Thread \n");
    return NULL;
}

int main() {
    pthread_t thread_id;
    printf("Before Thread\n");
    pthread_create(&thread_id, NULL, myThreadFun, NULL);
    pthread_join(thread_id, NULL);
    printf("After Thread\n");
    return 0;
}
