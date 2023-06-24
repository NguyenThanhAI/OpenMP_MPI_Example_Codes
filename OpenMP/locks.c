#include<stdio.h>
#include<omp.h>

int main(int argc, char** argv) {
    omp_lock_t lck;
    omp_init_lock(&lck);
    int id, tmp;
    #pragma omp parallel private (tmp, id)
    {
        id = omp_get_thread_num();
        tmp = id * id * id * id;
        omp_set_lock(&lck);
        printf("%d %d\n", id, tmp);
        omp_unset_lock(&lck);
    }
    omp_destroy_lock(&lck); 
    return 0;
}