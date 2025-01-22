#include "mpi.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_vovel(char *str) {
    int count; 
    const char *vovels = "aeiou";
    while(*str){
        char ch = tolower(*str);
        if(strchr(vovels, ch))
            count++;
        str++;
    }
    return count;
}

int main(int argc, char* argv[]) {
    int rank, size, len, local_not_vowel, *local_not_vowels, substr_len;
    char *str, *substr;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter String Length: ");
        scanf("%d", &len);
        str = (char *)malloc(sizeof(char) * len + 1);
        scanf("%s", str);
        substr_len = len / size;
    }

    MPI_Bcast(&substr_len, 1, MPI_INT, 0, MPI_COMM_WORLD);

    substr = (char *)malloc(substr_len * sizeof(char));
    MPI_Scatter(str, substr_len, MPI_CHAR, substr, substr_len, MPI_CHAR, 0, MPI_COMM_WORLD);
    
    local_not_vowel = substr_len - count_vovel(substr);

    if(rank == 0)
        local_not_vowels = (int *)malloc(size * sizeof(int));

    MPI_Gather(&local_not_vowel, 1, MPI_INT, local_not_vowels, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        int total_not_vowel = 0;
        for(int i=0; i < size; i++)
             total_not_vowel += local_not_vowels[i];
        printf("The total non vowels: %d\n", total_not_vowel);
    }
    MPI_Finalize();
}
