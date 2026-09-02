
#include <cuda_runtime.h>
#include <math.h>

__global__ void silu_kernel(const float *input, float *output, int N) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= N)
        return;

    float temp = 0;
    temp = 1 / (1 + exp(-input[idx]));
    output[idx] = input[idx] * temp;
}

// input, output are device pointers
extern "C" void solve(const float *input, float *output, int N) {
    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

    silu_kernel<<<blocksPerGrid, threadsPerBlock>>>(input, output, N);
    cudaDeviceSynchronize();
}
