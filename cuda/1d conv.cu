#include <cuda_runtime.h>

__global__ void convolution_1d_kernel(const float *input, const float *kernel,
                                      float *output, int input_size,
                                      int kernel_size) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < input_size - kernel_size + 1) {
        int p = 0;
        for (int i = idx, j = 0; i < idx + kernel_size && j < kernel_size;
             i++, j++) {
            p += input[i] * kernel[j];
        }
        output[idx] = p;
    }
}

// input, kernel, output are device pointers (i.e. pointers to memory on the
// GPU)
extern "C" void solve(const float *input, const float *kernel, float *output,
                      int input_size, int kernel_size) {
    int output_size = input_size - kernel_size + 1;
    int threadsPerBlock = 256;
    int blocksPerGrid = (output_size + threadsPerBlock - 1) / threadsPerBlock;

    convolution_1d_kernel<<<blocksPerGrid, threadsPerBlock>>>(
        input, kernel, output, input_size, kernel_size);
    cudaDeviceSynchronize();
}
