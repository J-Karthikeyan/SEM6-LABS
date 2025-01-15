#include<mpi.h>
#include<stdio.h>

int main(int argc, char** argv){
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    printf("GGs from process %d out of %d processes\n", rank, size);
    if(rank == 0){
        int data = 42;
        MPI_Send(&data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        printf("Process 0 sent data: %d to process 1\n", data);
    }else if(rank == 1){
        int data;
        MPI_Recv(&data, 1,  MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process 1 recieved data: %d from process 0\n", data);
    }
    MPI_Finalize();
    return 0;
}



