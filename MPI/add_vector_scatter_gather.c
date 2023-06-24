#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <mpi.h>

#define N 20


void initData(int *B, int *C, int n) {
    for(int i = 0; i < n; i++) {
        *(B + i) = i + 1;
        *(C + i) = 2 * (i + 1);
    }
}


int main(int argc, char** argv) {
    int rank, size;
    int count;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int ns = N / size;

    int *A, *B, *C;
    A = (int *)malloc(N * sizeof(int));
    B = (int *)malloc(N * sizeof(int));
    C = (int *)malloc(N * sizeof(int));

    int *As, *Bs, *Cs;

    As = (int *)malloc(ns * sizeof(int));
    Bs = (int *)malloc(ns * sizeof(int));
    Cs = (int *)malloc(ns * sizeof(int));

    if (rank == 0) {
        initData(B, C, N);

        for (int i = 0; i < ns; i++) {
            *(Bs + i) = *(B + i);
            *(Cs + i) = *(C + i);
        }
    }
    MPI_Scatter(B, ns, MPI_INT, Bs, ns, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(C, ns, MPI_INT, Cs, ns, MPI_INT, 0, MPI_COMM_WORLD);

    for(int i = 0; i < ns; i++) {
        *(As + i) = *(Bs + i) + *(Cs + i);
    }

    MPI_Gather(As, ns, MPI_INT, A, ns, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < N; i++) {
        printf("%d ", *(A + i));
    }
    }

    printf("\n");

    free(A);
    free(B);
    free(C);
    free(As);
    free(Bs);
    free(Cs);

    MPI_Finalize();

    return 0;
}