#include <stdio.h>
#include <omp.h>

int main() {
    #pragma omp parallel num_threads(4)
    {
        //#pragma omp single
        //{
            #pragma omp task
            printf("Task 1 executed by thread %d\n", omp_get_thread_num());

            #pragma omp task
            printf("Task 2 executed by thread %d\n", omp_get_thread_num());

            #pragma omp task
            printf("Task 3 executed by thread %d\n", omp_get_thread_num());

            #pragma omp taskwait

            printf("All tasks completed %d\n", omp_get_thread_num());
        //}
    }

    return 0;
}