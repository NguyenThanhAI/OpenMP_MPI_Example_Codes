#include <stdio.h>
#include <omp.h>

int main() {
    int shared_variable = 0;

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();

        //#pragma omp for
        for (int i = 0; i < 100; i++) {
            #pragma omp critical
            shared_variable += 1;
            printf("Thread %d: Incrementing shared_variable to %d\n", thread_id, shared_variable);
        }
    }

    printf("\nFinal value of shared_variable: %d\n", shared_variable);

    return 0;
}