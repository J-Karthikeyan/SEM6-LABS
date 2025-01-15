#include<stdio.h>
#include<mpi.h>

int main(int argc, char *argv[]){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank % 2){
        printf("World %d\n", rank);
    }else{
        printf("Hello %d\n", rank);
    }
    MPI_Finalize();
    return 0;
}
