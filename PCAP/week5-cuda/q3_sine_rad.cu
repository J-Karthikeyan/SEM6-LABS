#include<stdio.h>
#include<stdlib.h>
#include<cuda_runtime.h>
#include<math.h>

__global__ void sine_of_rad(float *rad, float *sine, int n){
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if(tid < n){
        sine[tid] = sin(rad[tid]); 
    }
}

int main(void){
    float *rad, *sine;
    float *d_rad, *d_sine;
    int N = 2048;
    size_t size = N * sizeof(float);

    rad = (float *)malloc(size);
    sine = (float *)malloc(size);
    
    cudaMalloc((void **)&d_rad, size);
    cudaMalloc((void **)&d_sine, size);

    for(int i=0; i<N; i++){
        rad[i] = 0.001 * i;
    }
    
    int threads_per_block = 256;
    // equivalent to ceil[N / 256]
    int blocks_per_grid = (N + threads_per_block - 1) / threads_per_block;

    cudaMemcpy(d_rad, rad, size, cudaMemcpyHostToDevice);
    
    sine_of_rad<<<blocks_per_grid, threads_per_block>>>(d_rad, d_sine, N);
    
    cudaMemcpy(sine, d_sine, size, cudaMemcpyDeviceToHost);
    
    // sample 10 results 
    for(int i=1; i<N; i+=128){
        printf("sine[%f] = %f\n", rad[i], sine[i]);
    }

    cudaFree(d_rad);
    cudaFree(d_sine);
    free(rad);
    free(sine);

    return 0;
}
