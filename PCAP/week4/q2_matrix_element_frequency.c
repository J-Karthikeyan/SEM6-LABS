#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size, target, matrix[3][3], sub_matrix[3], local_count = 0, global_count = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank == 0){
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                scanf("%d", &matrix[i][j]);
            }
        }
        printf("Target element: ");
        scanf("%d", &target);
    }    

    MPI_Bcast(matrix, 9, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&target, 1, MPI_INT, 0, MPI_COMM_WORLD);

    for(int i=0; i<3; i++){
        if (matrix[rank][i] == target) local_count++;
    }
    
    MPI_Scan(&local_count , &global_count, 1 , MPI_INT , MPI_SUM , MPI_COMM_WORLD);

    if(rank == size -1)
        printf("final frequency count: %d\n", global_count);

    MPI_Finalize();
    return 0;
}