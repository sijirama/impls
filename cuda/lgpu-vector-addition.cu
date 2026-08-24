
#include <cuda_runtime.h>

__global__ void vector_add(const float *A, const float *B, float *C, int N) {
    int baseIdx = blockIdx.x * blockDim.x + threadIdx.x;
    if (baseIdx >= N)
        return;
    C[baseIdx] = A[baseIdx] + B[baseIdx];
}

// A, B, C are device pointers (i.e. pointers to memory on the GPU)
extern "C" void solve(const float *A, const float *B, float *C, int N) {
    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

    vector_add<<<blocksPerGrid, threadsPerBlock>>>(A, B, C, N);
    cudaDeviceSynchronize();
}
