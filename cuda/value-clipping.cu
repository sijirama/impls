#include <cuda_runtime.h>

#define MIN(a, b) (a > b ? b : a)
#define CLIP(a, b, c) ((a < b) ? MIN(b, c) : MIN(a, c))

__global__ void clip_kernel(const float *input, float *output, float lo,
                            float hi, int N) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= N)
        return;

    output[idx] = CLIP(input[idx], lo, hi);
}

// input, output are device pointers
extern "C" void solve(const float *input, float *output, float lo, float hi,
                      int N) {
    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

    clip_kernel<<<blocksPerGrid, threadsPerBlock>>>(input, output, lo, hi, N);
    cudaDeviceSynchronize();
}
