#include <cuda_runtime.h>
#include <math.h>

__device__ float silu_kernel(float input) { return 1 / (1 + exp(-input)); }

__global__ void swiglu_kernel(const float *input, float *output, int halfN) {

    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= halfN)
        return;

    // swiglu index is halfN * 2 + idx
    output[idx] = silu_kernel(input[idx]) * input[halfN + idx];
}

// input, output are device pointers
extern "C" void solve(const float *input, float *output, int N) {
    int halfN = N / 2;
    int threadsPerBlock = 256;
    int blocksPerGrid = (halfN + threadsPerBlock - 1) / threadsPerBlock;

    swiglu_kernel<<<blocksPerGrid, threadsPerBlock>>>(input, output, halfN);
    cudaDeviceSynchronize();
}
