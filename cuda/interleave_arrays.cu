#include <cuda_runtime.h>

// solution 1

#include <cuda_runtime.h>

__global__ void interleave_kernel(const float *A, const float *B, float *output,
                                  int N) {

    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= N)
        return;

    // 0 -> 0 and 1
    // 1 -> 2 and 3
    // 2 -> 4 and 5
    // 3 -> 6 and 7
    // 4 -> 8 and 9

    output[idx * 2] = A[idx];
    output[idx * 2 + 1] = B[idx];
}

extern "C" void solve(const float *A, const float *B, float *output, int N) {
    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

    interleave_kernel<<<blocksPerGrid, threadsPerBlock>>>(A, B, output, N);
    cudaDeviceSynchronize();
}

// solution 2 - i changed the blocksPerGrid to N * 2 to provision more threads;
__global__ void interleave_kernel(const float *A, const float *B, float *output,
                                  int N) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= N * 2)
        return;
    if (idx % 2 != 0)
        return;
    idx = idx / 2;
    output[idx] = A[idx];
    output[idx + 1] = B[idx];
}

// A, B, output are device pointers (i.e. pointers to memory on the GPU)
extern "C" void solve(const float *A, const float *B, float *output, int N) {
    int threadsPerBlock = 256;
    int blocksPerGrid = (N * 2 + threadsPerBlock - 1) / threadsPerBlock;

    interleave_kernel<<<blocksPerGrid, threadsPerBlock>>>(A, B, output, N);
    cudaDeviceSynchronize();
}
