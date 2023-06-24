#include <stdio.h>
#include <omp.h>
#include <malloc.h>


#define N 100

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

int main(int argc, char** argv) {
    const int num_threads = 4;
    int *A, *B, *C;

    A = (int *)malloc(N * sizeof(int));
    B = (int *)malloc(N * sizeof(int));
    C = (int *)malloc(N * sizeof(int));

    init_data(B, C, N);


    free(A); free(B); free(C);
    return 0;
}