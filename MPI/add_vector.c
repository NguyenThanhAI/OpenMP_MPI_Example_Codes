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


int main(int argc, char *argv[]){
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

    //printf("Number of process: %d, Rank: %d", size, rank);

    if (rank == 0) {
        initData(B, C, N);
        for (int i = 1; i < size; i++) {
            MPI_Send(B + i * ns, ns, MPI_INT, i, i, MPI_COMM_WORLD);
            MPI_Send(C + i * ns, ns, MPI_INT, i, i, MPI_COMM_WORLD);
        }

        for (int i = 0; i < ns; i++) {
            *(Bs + i) = *(B + i);
            *(Cs + i) = *(C + i);
        }
    } else {
        MPI_Recv(Bs, ns, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
        // MPI_Get_count(&status, MPI_INT, &count);
        // printf("Item received %d, process %d\n", count, rank);
        MPI_Recv(Cs, ns, MPI_INT, 0, rank, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &count);
        printf("Item received %d, process %d\n", count, rank);
        MPI_Get_elements(&status, MPI_INT, &count);
        printf("Item gets %d, process %d\n", count, rank);
    }

    for(int i = 0; i < ns; i++) {
        *(As + i) = *(Bs + i) + *(Cs + i);
    }

    if (rank == 0) {
        for (int i = 0; i < ns; i++) {
            *(A + i) = *(As + i);
        }
        for (int i = 1; i < size; i++) {
            MPI_Recv(A + i * ns, ns, MPI_INT, i, i, MPI_COMM_WORLD, &status);
        }
    } else {
        MPI_Send(As, ns, MPI_INT, 0, rank, MPI_COMM_WORLD);
    }

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