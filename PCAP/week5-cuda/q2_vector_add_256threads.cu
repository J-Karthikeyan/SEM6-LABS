#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

__global__ void vector_add(int *A, int *B, int *C, int n) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if(tid < n) 
        C[tid] = A[tid] + B[tid];
    
}

int main(void){
    int *a, *b, *c;
    int *d_a, *d_b, *d_c;
    int N = 2048;
    size_t size = N * sizeof(int);

    a = (int *)malloc(size);
    b = (int *)malloc(size);
    c = (int *)malloc(size);

    cudaMalloc((void **)&d_a, size);
    cudaMalloc((void **)&d_b, size);
    cudaMalloc((void **)&d_c, size);

    for(int i=0; i<N; i++){
        a[i] = i;
        b[i] = 2 * i + 1;
    }

    int threads_per_block = 256;
    // equivalent to ceil[N / 256]
    int blocks_per_grid = (N + threads_per_block - 1) / threads_per_block;

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);
    
    vector_add<<<blocks_per_grid, threads_per_block>>>(d_a, d_b, d_c, N);
    
    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);
    
    // sample 10 results 
    for(int i=0; i<10; i++){
        printf("c[%d] = %d\n", i, c[i]);
    }

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    free(a);
    free(b);
    free(c);

}
