
#include <cuda_runtime.h>

__global__ void copy_matrix_kernel(const float *A, float *B, int total) {

    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    // int ty = blockIdx.y * blockDim.y + threadIdx.y;
    // int idx = tx * (blockDim.x * gridDim.x) + ty;
    if (idx > total)
        return;

    B[idx] = A[idx];
}

// A, B are device pointers (i.e. pointers to memory on the GPU)
extern "C" void solve(const float *A, float *B, int N) {
    int total = N * N;
    int threadsPerBlock = 256;
    int blocksPerGrid = (total + threadsPerBlock - 1) / threadsPerBlock;
    copy_matrix_kernel<<<blocksPerGrid, threadsPerBlock>>>(A, B, total);
    cudaDeviceSynchronize();
}
