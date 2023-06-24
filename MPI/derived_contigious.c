#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int count = 3;
    int data = 10;
    MPI_Datatype newtype;

    MPI_Type_contiguous(count, MPI_INT, &newtype);
    MPI_Type_commit(&newtype);

    if (rank == 0) {
        MPI_Send(&data, 1, newtype, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent data %d using derived data type.\n", data);
    } else if (rank == 1) {
        MPI_Recv(&data, 1, newtype, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received data %d using derived data type.\n", data);
    }

    MPI_Type_free(&newtype);
    MPI_Finalize();
    return 0;
}