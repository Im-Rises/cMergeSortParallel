#include <stdio.h>
#include <omp.h>

int main()
{
// #pragma omp for
//     for (int i=0;i <1000;i++)
//     {
//         printf("Thread: %d - Value: %d\n", omp_get_thread_num(),i);
//     }
#pragma omp parallel
    {
#pragma omp task
        printf("1 %d: ", omp_get_thread_num());
#pragma omp task
        printf("2 %d: ", omp_get_thread_num());
#pragma omp task
        printf("3 %d: ", omp_get_thread_num());
#pragma omp task
        printf("4 %d: ", omp_get_thread_num());
    }
}
