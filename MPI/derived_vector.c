#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int rows = 2;
    int cols = 3;
    int stride = cols + 1;  // Stride of 1 row + 1 column
    int data[rows][cols] = {{ 1, 2, 3 },{ 4, 5, 6 }};
    MPI_Datatype newtype;

    MPI_Type_vector(rows, cols, stride, MPI_INT, &newtype);
    MPI_Type_commit(&newtype);

    if (rank == 0) {
        MPI_Send(&data[0][0], 1, newtype, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent data using derived data type.\n");
    } else if (rank == 1) {
        MPI_Recv(&data[0][0], 1, newtype, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received data using derived data type.\n");
        printf("Received data: %d %d %d %d %d %d\n", data[0][0], data[0][1], data[0][2], data[1][0], data[1][1], data[1][2]);
    }

    MPI_Type_free(&newtype);
    MPI_Finalize();
    return 0;
}