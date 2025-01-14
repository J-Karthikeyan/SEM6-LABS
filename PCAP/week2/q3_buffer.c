#include "mpi.h"
#include <stdio.h>
#include<stdlib.h>

int main(int argc, char * argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    int buffer_size = size * sizeof(int) + MPI_BSEND_OVERHEAD;
    char *buffer = (char *)malloc(buffer_size);  
    MPI_Buffer_attach(buffer, buffer_size);  

    if (rank == 0) {  
        int arr[size - 1];
        printf("Enter %d elements:\n", size - 1);
        for (int i = 0; i < size - 1; i++) {
            scanf("%d", &arr[i]);
            MPI_Bsend(&arr[i], 1, MPI_INT, i + 1, 0, MPI_COMM_WORLD);
        }
    } else {
        int num;
        MPI_Recv(&num, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        if (rank % 2 == 0) {
            printf("Rank: %d received: %d square: %d\n", rank, num, num * num);
        } else {
            printf("Rank: %d received: %d cube: %d\n", rank, num, num * num * num);
        }
    }
    MPI_Buffer_detach(&buffer, &buffer_size);
    free(buffer);  

    MPI_Finalize();
    return 0;
}
