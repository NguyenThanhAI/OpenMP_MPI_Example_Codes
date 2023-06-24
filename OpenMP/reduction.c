#include <stdio.h>
#include <omp.h>
#include <time.h>

int main(int argc, char** argv) {
    int i=1;
    #pragma omp parallel reduction(*:i)
    {
        i=omp_get_num_threads();
        printf("%d\n", i);
    }
    printf("result=%d\n", i); 

    // int sum = 0;
    // int id;

    // #pragma omp parallel for reduction(+: sum)
    // for (int i = 1; i <= 10; i++) {
    //     //id = omp_get_thread_num();
    //     sum += i;
    //     //printf("id: %d, i: %d\n", id, i);
    // }

    // printf("The sum is: %d\n", sum);
    return 0;
}

// #include <stdio.h>
// #include <omp.h>

// int main() {
//     int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//     int sum = 0;
//     int product = 1;
//     int max_value = array[0];
//     int min_value = array[0];

//     #pragma omp parallel for //reduction(+: sum) reduction(*: product) reduction(max: max_value) reduction(min: min_value)
//     for (int i = 0; i < 10; i++) {
//         sum += array[i];        // Reduction: Summation
//         product *= array[i];    // Reduction: Product
//         max_value = (array[i] > max_value) ? array[i] : max_value;
//         min_value = (array[i] < min_value) ? array[i] : min_value;
//         printf("%d\n", omp_get_thread_num());
//     }

//     printf("Sum: %d\n", sum);
//     printf("Product: %d\n", product);
//     printf("Max: %d\n", max_value);
//     printf("Min: %d\n", min_value);

//     return 0;
// }