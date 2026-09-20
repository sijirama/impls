#include <cuda_runtime.h>

__global__ void k(const int *input, int *histogram, int N, int num_bins) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= N)
        return;

    int index = input[idx];
    atomicAdd(&histogram[index], 1);
}

// input, histogram are device pointers
extern "C" void solve(const int *input, int *histogram, int N, int num_bins) {

    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

    // we need to assert all values in histogram are 0
    k<<<blocksPerGrid, threadsPerBlock>>>(input, histogram, N, num_bins);
    cudaDeviceSynchronize();
}
