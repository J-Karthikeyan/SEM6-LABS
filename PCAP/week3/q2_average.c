#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

double average(int* arr, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    return sum / n;
}

int main(int argc, char *argv[]) {
    int rank, size, N, M, *arr, *subarr, arr_size;
    double local_avg, total_avg, *local_avgs;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        N = size;
        fprintf(stdout, "Enter M:\n");
        scanf("%d", &M);
        arr_size = M * N;
        arr = (int *)malloc(arr_size * sizeof(int));
        fprintf(stdout, "Enter %d elements:\n", arr_size);
        fflush(stdout);
        
        for (int i = 0; i < arr_size; i++) {
            scanf("%d", &arr[i]);  
        }
    }

    MPI_Bcast(&M, 1, MPI_INT, 0, MPI_COMM_WORLD);
    subarr = (int *)malloc(M * sizeof(int));
    MPI_Scatter(arr, M, MPI_INT, subarr, M, MPI_INT, 0, MPI_COMM_WORLD);
    local_avg = average(subarr, M);

    if (rank == 0) {
        local_avgs = (double *)malloc(N * sizeof(double));
    }
    MPI_Gather(&local_avg, 1, MPI_DOUBLE, local_avgs, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        double sum_avg = 0.0;
        for (int i = 0; i < N; i++)
            sum_avg += local_avgs[i];
        total_avg = sum_avg / N;
        fprintf(stdout, "Total average: %f\n", total_avg);  // Fixed: %f for double
        fflush(stdout);
        free(arr);
        free(local_avgs);
    }
    free(subarr);
    MPI_Finalize();
    return 0;
}
