#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
    int rank, size;
    int nnodes = 4;
    int index[4] = {2, 2, 2, 2};
    int edges[8] = {1, 3, 0, 2, 2, 0, 3, 1};
    MPI_Comm comm_graph;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Graph_create(MPI_COMM_WORLD, nnodes, index, edges, 0, &comm_graph);

    int graph_rank, graph_size;
    MPI_Comm_rank(comm_graph, &graph_rank);
    MPI_Comm_size(comm_graph, &graph_size);

    printf("Process %d (global rank) / %d (graph rank) out of %d (global size) / %d (graph size)\n",
           rank, graph_rank, size, graph_size);

    MPI_Comm_free(&comm_graph);
    MPI_Finalize();
    return 0;
}