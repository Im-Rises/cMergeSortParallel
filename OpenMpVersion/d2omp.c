#include <stdio.h>
#include <omp.h>

int main() {
    printf("%d", omp_get_max_threads());
    return 0;
}
