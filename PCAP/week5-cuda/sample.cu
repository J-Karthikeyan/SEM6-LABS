#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>

// CUDA kernel definition
__global__ void vector_add(float* A, float* B, float* C, int n)
{
    // Calculate unique thread index
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    
    // Ensure we don't exceed array bounds
    if(tid < n) {
        C[tid] = A[tid] + B[tid];
    }
}

int main(void)
{
    const int N = 1 << 20;  // 1 million elements (1048576)
    size_t size = N * sizeof(float);
    float *h_A, *h_B, *h_C;  // Host pointers
    float *d_A, *d_B, *d_C;  // Device pointers

    // 1. Allocate host memory
    h_A = (float*)malloc(size);
    h_B = (float*)malloc(size);
    h_C = (float*)malloc(size);

    // 2. Allocate device memory
    cudaMalloc((void**)&d_A, size);
    cudaMalloc((void**)&d_B, size);
    cudaMalloc((void**)&d_C, size);

    // 3. Initialize host arrays
    for(int i = 0; i < N; i++) {
        h_A[i] = 1.0f;
        h_B[i] = 2.0f;
    }

    // 4. Copy data to device
    cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

    // 5. Configure and launch kernel
    int threads_per_block = 256;
    int blocks_per_grid = (N + threads_per_block - 1) / threads_per_block;
    
    vector_add<<<blocks_per_grid, threads_per_block>>>(d_A, d_B, d_C, N);
    
    // Wait for GPU to finish
    cudaDeviceSynchronize();

    // 6. Copy result back to host
    cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);

    // 7. Verify result
    for(int i = 0; i < 10; i++) {
        printf("h_C[%d] = %.2f\n", i, h_C[i]);
    }

    // 8. Cleanup
    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
    free(h_A);
    free(h_B);
    free(h_C);

    return 0;
}
