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

    int sum = 0;
    int i, id;
    start = clock();
    #pragma omp parallel for schedule(static, N/num_threads) private(id)
    for(i = 0; i < N; i++) {
        //sum++;
        A[i] = B[i] + C[i];
        //id = omp_get_thread_num();
        //printf("i: %d, thread num: %d\n", i, id);
    }
    end = clock();
    time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    //display(A, N);
    printf("Parallel %.2lf\n", time_used);
    free(A); free(B); free(C);

    return 0;
}