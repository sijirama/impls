
#include <cuda_runtime.h>

__global__ void rgb_to_grayscale_kernel(const float *input, float *output,
                                        int width, int height) {

    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx >= width * height)
        return;

    // 0 -> 0,1,2
    // 1 -> 3,4,5
    // 2 -> 6,7,8
    // 3 -> 9,10,11

    output[idx] = 0.299 * input[idx * 3] + 0.587 * input[idx * 3 + 1] +
                  0.114 * input[idx * 3 + 2];
}

// input, output are device pointers
extern "C" void solve(const float *input, float *output, int width,
                      int height) {
    int total_pixels = width * height;
    int threadsPerBlock = 256;
    int blocksPerGrid = (total_pixels + threadsPerBlock - 1) / threadsPerBlock;

    rgb_to_grayscale_kernel<<<blocksPerGrid, threadsPerBlock>>>(input, output,
                                                                width, height);
    cudaDeviceSynchronize();
}
