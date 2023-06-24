#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int dims[2] = {4, 4};  // Kích thước từng chiều
    int periods[2] = {1, 0};  // Chu kỳ từng chiều
    int coords[2];  // Tọa độ của tiến trình hiện tại trên ô lưới Decarted
    int left, right, up, down;  // Các láng giềng trên ô lưới

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != dims[0] * dims[1]) {
        printf("Number of processes must match the grid size.\n");
        MPI_Finalize();
        return 0;
    }

    MPI_Comm cart_comm;
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &cart_comm);
    MPI_Cart_coords(cart_comm, rank, 2, coords);

    MPI_Cart_shift(cart_comm, 0, 1, &left, &right);
    MPI_Cart_shift(cart_comm, 1, 1, &up, &down);

    printf("Rank %d: Coordinates (%d, %d), neighbors (left: %d, right: %d, up: %d, down: %d)\n",
           rank, coords[0], coords[1], left, right, up, down);

    MPI_Comm_free(&cart_comm);
    MPI_Finalize();
    return 0;
}