#include <stdio.h>
#include <omp.h>
#include <time.h>


int main(int argc, char** argv) {
    int i, k=2, N = 100;
    double A[N], B[N], C[N];
    int id;
    omp_set_num_threads(8);
    //struct timespec start, stop;
    for (i = 0; i < N; i++) {
        B[i] = 1;
        C[i] = 1;
    }
    // clock_gettime(CLOCK_REALTIME, &start);
    for(i = 0; i < N; i++) {
        A[i] = B[i] + 2 * C[i];
    }
    // clock_gettime(CLOCK_REALTIME, &stop);
    // double result = (stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_nsec - start.tv_nsec) / 1e3; // in microseconds

    // printf("Raw elapsed time: %f us\n", result);

    // clock_gettime(CLOCK_REALTIME, &start);
    int sum = 0;
    #pragma omp parallel for private(id)
    for(i = 0; i < N; i++) {
        sum++;
        A[i] = B[i] + 2 * C[i];
        id = omp_get_thread_num();
        printf("i: %d, thread num: %d\n", i, id);
    }
    // clock_gettime(CLOCK_REALTIME, &stop);
    // result = (stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_nsec - start.tv_nsec) / 1e3; // in microseconds
    printf("steps: %d\n", sum);
    for (i = 0; i < N; i++) {
        printf("%.1f %d\n", A[i], i);
    }
    // printf("OpenMP elapsed time: %f us\n", result);
    return 0;
}