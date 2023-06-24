#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel num_threads(4)
    #pragma omp for ordered
    for (int i = 0; i < 100; i++) {
        #pragma omp ordered
        printf("i: %d, thread id: %d\n", i, omp_get_thread_num());
    }

    return 0;
}