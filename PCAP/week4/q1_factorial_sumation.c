#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int factorial(int n) {
    if (n < 2) return 1;
    return n * factorial(n - 1);
}

int main(int argc, char *argv[]) {
    int rank, size, fact_sum = 0, fact = 1, local_fact;
    int error_code; 
    char error_string[MPI_MAX_ERROR_STRING]; 
    int error_length; 
    int error_class; 

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_set_errhandler( MPI_COMM_WORLD , MPI_ERRORS_RETURN);
    local_fact = factorial(rank + 1);

    // For datatype error
    MPI_Datatype MPI_Int;

    // For comm error
    // MPI_Comm MPI_COMM_NULL;
    // error_code = MPI_Scan(&local_fact, &fact_sum, 1, MPI_Int, MPI_SUM, MPI_COMM_NULL);
    error_code = MPI_Scan(&local_fact, &fact_sum, 1, MPI_Int, MPI_SUM, MPI_COMM_WORLD);

    if (error_code != MPI_SUCCESS) {
        MPI_Error_class(error_code, &error_class);
        MPI_Error_string(error_class, error_string, &error_length);
        
        printf("| Error class: %d | Error code: %d | Error message: %s |\n", error_class, error_code, error_string);
    } else {
        if (rank == size - 1) {
            printf("Summation of factorials: %d\n", fact_sum);
        }
    }

    MPI_Finalize();
    return 0;
}
