#include <stdio.h>
#include <mpi.h>

typedef struct {
    int x;
    int y;
} Point;

int main(int argc, char** argv) {
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    Point p;
    MPI_Datatype point_type;
    int block_lengths[2] = {1, 1};
    MPI_Aint displacements[2] = {0, sizeof(int)};
    MPI_Datatype types[2] = {MPI_INT, MPI_INT};

    MPI_Type_create_struct(2, block_lengths, displacements, types, &point_type);
    MPI_Type_commit(&point_type);

    if (rank == 0) {
        p.x = 10;
        p.y = 20;
        MPI_Send(&p, 1, point_type, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent point (%d, %d) to process 1.\n", p.x, p.y);
    } else if (rank == 1) {
        MPI_Recv(&p, 1, point_type, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 received point (%d, %d) from process 0.\n", p.x, p.y);
    }

    MPI_Type_free(&point_type);
    MPI_Finalize();
    return 0;
}