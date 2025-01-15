#include<mpi.h>
#include<stdio.h>
#include<math.h>

int main(int argc, char *argv[]){
    int rank, size, x = 7;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("Process: %d, and pow(x, rank) = %f", rank, pow(x, rank));
    MPI_Finalize();
    return 0;
}
