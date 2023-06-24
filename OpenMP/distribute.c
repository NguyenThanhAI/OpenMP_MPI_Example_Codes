#include <stdio.h>
#include <omp.h>
#include <malloc.h>
#include <time.h>


#define N 10000000

void init_data(int *B, int *C, int n) {
    for (int i = 0; i < n; i++) {
        *(B + i) = (i + 1);
        *(C + i) = 2 * (i + 1);
    }
}

void display(int *A, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", *(A + i));
    }
    printf("\n");
}

void sequential_add(int *A, int *B, int *C, int n) {
    for (int i = 0; i < n; i++) {
        *(A + i) = *(B + i) + *(C + i);
    }
}


int main(int argc, char** argv) {
    clock_t start, end;
    double time_used;
    const int num_threads = 4;
    int *A, *B, *C;

    A = (int *)malloc(N * sizeof(int));
    B = (int *)malloc(N * sizeof(int));
    C = (int *)malloc(N * sizeof(int));

    init_data(B, C, N);

    start = clock();
    sequential_add(A, B, C, N);
    end = clock();
    time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Sequential %.2lf\n", time_used);

    omp_set_num_threads(num_threads);

    start = clock();
    #pragma omp parallel
    {
        int id = omp_get_thread_num();
        int start = id * (N / num_threads);
        int end = (id + 1) * (N / num_threads);
        for (int i = start; i < end; i++) {
            *(A + i) = *(B + i) + *(C + i);
        }
        #pragma omp barrier
    }

    end = clock();
    time_used = ((double) (end - start)) / CLOCKS_PER_SEC;


    //display(A, N);
    printf("Parallel %.2lf\n", time_used);
    free(A); free(B); free(C);
    return 0;
}