#include "mpi.h"
#include<stdio.h> 

int main(int argc, char * argv[]){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    if (rank == 0){
        int len;
        printf("size of array: "); scanf("%d", &len);
        int arr[len];

        for(int i=0; i<len; i++){
            scanf("%d", arr + i);
            MPI_Send(arr + i, 1, MPI_INT, i+1, 0, MPI_COMM_WORLD);
        } 
    } else{
        int num;
        MPI_Recv(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        fprintf(stdout, "Rank: %d Recieved: %d\n", rank, num);
        fflush(stdout);
    }
    MPI_Finalize();
    return 0;
}