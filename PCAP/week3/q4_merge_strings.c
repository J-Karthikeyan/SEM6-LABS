#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char* argv[]) {
    int rank, size, len, local_len;
    char *S1, *S2, *local_S1, *local_S2, *result, *local_result;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter length of strings: ");
        scanf("%d", &len);

        S1 = (char*)malloc(len * sizeof(char));
        S2 = (char*)malloc(len * sizeof(char));

        printf("Enter String S1: ");
        scanf("%s", S1);
        printf("Enter String S2: ");
        scanf("%s", S2);
    }

    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);

    local_len = len / size;

    local_S1 = (char*)malloc(local_len * sizeof(char));
    local_S2 = (char*)malloc(local_len * sizeof(char));
    local_result = (char*)malloc((local_len * 2) * sizeof(char)); 

    MPI_Scatter(S1, local_len, MPI_CHAR, local_S1, local_len, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Scatter(S2, local_len, MPI_CHAR, local_S2, local_len, MPI_CHAR, 0, MPI_COMM_WORLD);

    for (int i = 0; i < local_len; i++) {
        local_result[2 * i] = local_S1[i];  
        local_result[2 * i + 1] = local_S2[i];  
    }

    if (rank == 0) {
        result = (char*)malloc(len * 2 * sizeof(char));  
    }

    MPI_Gather(local_result, local_len * 2, MPI_CHAR, result, local_len * 2, MPI_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Resultant String: %s\n", result);
        free(S1);
        free(S2);
        free(result);
    }
    free(local_S1);
    free(local_S2);
    free(local_result);

    MPI_Finalize();
    return 0;
}
