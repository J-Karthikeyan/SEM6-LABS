#include "mpi.h"
#include<stdio.h>

int main(int argc, char *argv[]){
    MPI_Init(&argc, &argv);
    int rank, size, a = 12, b = 8;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    switch (rank)
    {
    case 0:
        printf("%d + %d = %d\n", a, b, a + b);
        break;
    case 1:
        printf("%d - %d = %d\n", a, b, a - b);
    case 2:
        printf("%d * %d = %ld\n", a, b, a * b);
    case 3:
        printf("%d / %d = %lf\n", a, b, a / (float)b);
    default:
        printf("calculator");
        break;
    }
    MPI_Finalize();
    return 0;
}
