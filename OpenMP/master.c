#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv) {

    int id, num_threads;

    #pragma omp parallel
    {
        id = omp_get_thread_num();
        num_threads = omp_get_num_threads();

        #pragma omp critical
        {
            printf("Thread %d id of %d threads\n", id, num_threads);
        }
        #pragma omp barrier
        printf("Thread %d id\n", id);
    }
    return 0;
}