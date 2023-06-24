#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv) {

    int id = 0;

    #pragma omp parallel private(id)
    {
        id = omp_get_thread_num();
        printf("Thread id %d\n", id);
    }
    printf("Thread %d id\n", id);
    return 0;
}