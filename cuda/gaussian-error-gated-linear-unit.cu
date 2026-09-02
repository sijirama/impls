#include <cmath>
#include <cuda_runtime.h>
#include <math.h>

__device__ float gelu_kernel(float input) {
    double pi = M_PI;
    return (0.5 * input) *
           (1 + tanh(sqrt(2 / pi) * (input + 0.044715 * (powf(input, 3)))));
}

__global__ void geglu_kernel(const float *input, float *output, int halfN) {

    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= halfN)
        return;

    output[idx] = input[idx] * gelu_kernel(input[halfN + idx]);
}

// input, output are device pointers
extern "C" void solve(const float *input, float *output, int N) {
    int halfN = N / 2;
    int threadsPerBlock = 256;
    int blocksPerGrid = (halfN + threadsPerBlock - 1) / threadsPerBlock;

    geglu_kernel<<<blocksPerGrid, threadsPerBlock>>>(input, output, halfN);
    cudaDeviceSynchronize();
}
