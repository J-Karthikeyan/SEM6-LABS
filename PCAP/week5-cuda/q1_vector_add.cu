#include<stdio.h>
#include<stdlib.h>
#include<cuda_runtime.h>

__global__ void vector_add(int* A, int* B, int* C, int n) {
    int tid = blockIdx.x * blockDim.x + threadIdx.x;
    if(tid < n) {
        C[tid] = A[tid] + B[tid];
    }
}

int main(void){
    int *a, *b, *c;
    int *d_a, *d_b, *d_c;
    const int N = 10;
    size_t size = N * sizeof(int);

    a = (int *)malloc(size);
    b = (int *)malloc(size);
    c = (int *)malloc(size);

    cudaMalloc((void **)&d_a, size);
    cudaMalloc((void **)&d_b, size);
    cudaMalloc((void **)&d_c, size);
    int flag = 0;
    printf("0 - (a) N blocks | 1 - (b) N threads : ");
    scanf("%d", &flag);
    printf("Enter %d integers for vector a: ", N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &a[i]);
    }

    printf("Enter %d integers for vector b: ", N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &b[i]);
    }

    cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);

    if (flag == 0) {
        vector_add<<<N, 1>>>(d_a, d_b, d_c, N);
    } else {
        vector_add<<<1, N>>>(d_a, d_b, d_c, N);
    }

    cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

    for (int i = 0; i < N; i++) {
        printf("c[%d] = %d\n", i, c[i]);
    }

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);
    free(a);
    free(b);
    free(c);

    return 0;
}
