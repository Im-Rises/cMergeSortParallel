#ifndef MERGE_SORT_PARALLEL_PTHREAD_H
#define MERGE_SORT_PARALLEL_PTHREAD_H

#define MULTITHREAD_THRESHOLD 1000

/*typedef enum Boolean Boolean;*/
enum Boolean {
    False = 0,
    True = 1
};

typedef struct ThreadState ThreadState;
struct ThreadState {
    pthread_t thread;
    enum Boolean isUsed;
};

typedef struct MergeSortArgs MergeSortArgs;
struct MergeSortArgs {
    int* A;
    int size;
    int* B;
    ThreadState* threads;
    int threadsNumber;
    pthread_mutex_t* myMutex;
};

void mergeSortParallelPThread(int A[], int arraySize, int B[], int threadsNumber);
static void mergeSortParallel(int A[], int arraySize, int B[], ThreadState* threads, int threadsNumber, pthread_mutex_t* myMutex);
static int checkThreadIsAvailable(ThreadState* threads, int threadsNumber);
static void* mergeSortParallelThread(void* input);

#endif
