#include "mpi.h"
#include <stdio.h>

char toggle(char c) {
    if (c >= 'A' && c <= 'Z') 
        return (c + ('a' - 'A'));
    else if (c >= 'a' && c <= 'z') 
        return (c - ('a' - 'A'));
    return c; 
}

char word[] = "heLLo";  

int main(int argc, char * argv[]) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    
    if (rank == 0) {
        MPI_Ssend(word, 6, MPI_CHAR, 1, 1, MPI_COMM_WORLD); 
        fprintf(stdout, "Sent %s\n", word);
        fflush(stdout);
    } else {
        MPI_Recv(word, 6, MPI_CHAR, 0, 1, MPI_COMM_WORLD, &status);  
        for (int i = 0; i < 5; i++) {  
            word[i] = toggle(word[i]);
        }
        word[5] = '\0';  
        fprintf(stdout, "Received %s\n", word);
        fflush(stdout);
    }
    
    MPI_Finalize();
    return 0;
}
