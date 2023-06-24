#include <stdio.h>
#include <omp.h>
#include <malloc.h>
#include <time.h>

#define M 30
#define N 40
#define P 50

void init_data(int *matrix, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            *(matrix + n * i + j) = 1;
        }
    }
}

void sequential_mul(int *A, int *B, int *C, int m, int n, int p) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < p; j++) {
            int temp = 0;
            for (int k = 0; k < n; k++) {
                //printf("%d, %d, %d\n", i, j, k);
                temp += *(B + i * n + k) * *(C + k * p + j);
            }
            *(A + i * p + j) = temp;
        }
    }
}

void display(int *matrix, int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", *(matrix + n * i + j));
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char** argv) {
    //clock_t start, end;
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    double time_used;
    int *A, *B, *C;
    A = (int *) malloc(M * P * sizeof(int));
    B = (int *) malloc(M * N * sizeof(int));
    C = (int *) malloc(N * P * sizeof(int));

    init_data(B, M, N);
    init_data(C, N, P);
    //display(B, M, N);
    //display(C, N, P);

    //start = clock();
    clock_gettime(CLOCK_REALTIME, &start);
    sequential_mul(A, B, C, M, N, P);
    //end = clock();
    clock_gettime(CLOCK_REALTIME, &end);
    //time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    time_used = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec) / 1e3;
    printf("Sequential %.2lf\n", time_used);
    //display(A, M, P);

    clock_gettime(CLOCK_REALTIME, &start);
    int i, j , k;
    #pragma omp parallel for collapse(2) private(i, j, k) shared(A, B, C)
    for (i = 0; i < M; i++) {
        for (j = 0; j < P; j++) {
            int temp = 0;
            for (k = 0; k < N; k++) {
                //printf("%d, %d, %d\n", i, j, k);
                temp += *(B + i * N + k) * *(C + k * P + j);
            }
            *(A + i * P + j) = temp;
        }
    }
    clock_gettime(CLOCK_REALTIME, &end);
    time_used = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
    printf("Parallel %.2lf\n", time_used);

    //display(A, M, P);

    free(A); free(B); free(C);
    return 0;
}