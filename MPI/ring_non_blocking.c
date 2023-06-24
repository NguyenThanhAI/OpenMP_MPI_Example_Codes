#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int data_send, data_recv;
    MPI_Request request;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    data_send = rank;

    // Send data in a ring from process 0 to process (size - 1)
    MPI_Isend(&data_send, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD, &request);
    MPI_Recv(&data_recv, 1, MPI_INT, (rank + size - 1) % size, 0, MPI_COMM_WORLD, &status);
    MPI_Wait(&request, &status);
    // MPI_Send(&data_send, 1, MPI_INT, (rank + 1) % size, 0, MPI_COMM_WORLD);
    // MPI_Recv(&data_recv, 1, MPI_INT, (rank + size - 1) % size, 0, MPI_COMM_WORLD, &status);

    printf("Process %d received data: %d\n", rank, data_recv);

    MPI_Finalize();
    return 0;
}