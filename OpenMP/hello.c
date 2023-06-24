#include<stdio.h>
#include<omp.h>

int main(int argc, char** argv) {
    int num_threads = 10;
    omp_set_num_threads(num_threads);
    int thread_id;
    #pragma omp parallel private(thread_id)
    {
        thread_id = omp_get_thread_num();
        printf("Hello from thread id %d\n", thread_id);
    }
    return 0;
}