#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>

int reverse_digits(int num){
    int res = 0;
    while(num){
        res = res * 10 + (num % 10);
        num /= 10;
    }
    return res;
}

int main(int argc, char *argv[]){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int arr[] = {18, 523, 310, 1234, 2, 14, 108, 150, 1928};
    printf("rank: %d num: %d reversed: %d\n", rank, arr[rank], reverse_digits(arr[rank]));
    MPI_Finalize();
    return 0;
}
