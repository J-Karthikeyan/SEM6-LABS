#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>

#define SIZE 4

void print_matrix(int matrix[SIZE][SIZE]){
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]){
    int rank, size, matrix[SIZE][SIZE], final_matrix[SIZE][SIZE], local_row[SIZE], out_row[SIZE];
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Scatter(matrix, SIZE, MPI_INT, local_row, SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Scan(local_row, out_row, SIZE, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    MPI_Gather(out_row, SIZE, MPI_INT, final_matrix, SIZE, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        printf("Original Matrix\n");
        print_matrix(final_matrix);
        printf("Final Matrix\n");
        print_matrix(final_matrix);
    }

    MPI_Finalize();
    return 0;
}
