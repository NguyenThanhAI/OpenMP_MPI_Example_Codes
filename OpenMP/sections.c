#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv) {


    omp_set_num_threads(4);
    int id;

    #pragma omp parallel private(id)
    {
        int id = omp_get_thread_num();
        #pragma omp sections nowait
        {
            #pragma omp section
            printf("1 + 1, id: %d\n", id);
            #pragma omp section
            printf("1 + 2, id: %d\n", id);
            #pragma omp section
            printf("1 + 3, id: %d\n", id);
        }
        printf("%d\n", id);
    }
    
    return 0;
}