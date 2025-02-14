#include "mpi.h"
#include<stdio.h>
#include<math.h>
#include<stdlib.h>`

int is_prime(int num){
    for(int i=2; i<sqrt(num); i++){
        if(num % i == 0) return 0;
    }
    return 1;
}

int main(int argc, char *argv[]){
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int s, e;
    int start = 1, end = 100, mid;
    mid = (end - start) / 2 + start;

    if (rank == 0){
        s = start;
        e = mid;
    } else{
        s = mid + 1;
        e = end;
    }

    int local_primes[50], local_count = 0;
    for(int i=s; i<e; i++){
        if (is_prime(i))
            local_primes[local_count++] = i;
    }

    if(rank == 0){
        
    }

}
