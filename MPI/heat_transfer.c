#include <mpi.h>
#include <stdio.h>
#include <malloc.h>

#define m 100

float dx = 1.0 / m, dt = 0.01;
float D = 0.1;

void DHB2(float *Ts, float Tl, float Tr, float *dTs, int ms) {
    int i;
    float c, l, r;
    for (i = 0; i < ms; i++) {
        c = *(Ts + i);
        l = (i == 0) ? Tl : *(Ts + i - 1);
        r = (i == ms - 1) ? Tr : *(Ts + i + 1);
        *(dTs + i) = D * (l - 2 * c + r) / (dx * dx);
    }
}

int main(int argc, char *argv[]) {
    int i, ms, size, rank;
    int num_steps = 100;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    ms = m / size;

    float *Ts, *T, *dT, *dTs;
    Ts = (float *)malloc(ms * sizeof(float));
    T = (float *)malloc(m * sizeof(float));
    dTs = (float *)malloc(ms * sizeof(float));
    dT = (float *)malloc(m * sizeof(float));

    float Tl, Tr;

    if (rank == 0) {
        for (int i = 0; i < m; i++) {
            *(T + i) = 25;
            *(dT + i) = 0;
        }

        for (int i = 0; i < ms; i++) {
            *(Ts + i) = *(T + i);
            *(dTs + i) = *(dT + i);
        }

        for (int k = 1; k < size; k++) {
            MPI_Send(T + ms * k, ms, MPI_FLOAT, k, k, MPI_COMM_WORLD);
            MPI_Send(dT + ms * k, ms, MPI_FLOAT, k, 1000 + k, MPI_COMM_WORLD);
        }
    } else {
        MPI_Recv(Ts, ms, MPI_FLOAT, 0, rank, MPI_COMM_WORLD, &status);
        MPI_Recv(dTs, ms, MPI_FLOAT, 0, 1000 + rank, MPI_COMM_WORLD, &status);
    }

    for (int i = 0; i < num_steps; i++) {
        // Truyen Tl
        if (rank == 0) {
            Tl = 100;
            MPI_Recv(&Tr, 1, MPI_FLOAT, 1, 1, MPI_COMM_WORLD, &status);
            MPI_Send(T + ms - 1, 1, MPI_FLOAT, 1, 1, MPI_COMM_WORLD);
        } else {
            if (rank == size - 1) {
                Tr = 25;
                MPI_Recv(&Tl, 1, MPI_FLOAT, rank - 1, rank - 1, MPI_COMM_WORLD, &status);
                MPI_Send(Ts, 1, MPI_FLOAT, rank - 1, rank - 1, MPI_COMM_WORLD);
            } else {
                MPI_Recv(&Tl, 1, MPI_FLOAT, rank - 1, rank, MPI_COMM_WORLD, &status);
                MPI_Recv(&Tr, 1, MPI_FLOAT, rank + 1, rank, MPI_COMM_WORLD, &status);
                MPI_Send(Ts, 1, MPI_FLOAT, rank - 1, rank - 1, MPI_COMM_WORLD);
                MPI_Send(Ts + ms - 1, 1, MPI_FLOAT, rank + 1, rank + 1, MPI_COMM_WORLD);
            }
        }

        DHB2(Ts, Tl, Tr, dTs, ms);
        for (int i = 0; i < ms; i++) {
            *(Ts + i) += dt * *(dTs + i);
        }
    }

    if (rank != 0) {
        MPI_Send(Ts, ms, MPI_FLOAT, 0, rank, MPI_COMM_WORLD);
    } else {
        for (int k = 1; k < size; k++) {
            MPI_Recv(T + ms * k, ms, MPI_FLOAT, k, k, MPI_COMM_WORLD, &status);
        }

        for (int i = 0; i < m; i++) {
            printf("%.4f ", *(T + i));
        }
        printf("\n");
    }

    free(Ts);
    free(T);
    free(dTs);
    free(dT);
    MPI_Finalize();
    return 0;
}