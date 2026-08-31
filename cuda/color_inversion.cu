

#include <cstdlib>
#include <cuda_runtime.h>

__global__ void invert_kernel(unsigned char *image, int width, int height) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < (width * height * 4) && ((idx + 1) % 4 != 0)) {
        image[idx] = 255 - image[idx];
    }
}

extern "C" void solve(unsigned char *image, int width, int height) {
    int threadsPerBlock = 256;
    int blocksPerGrid =
        (width * height * 4 + threadsPerBlock - 1) / threadsPerBlock;

    invert_kernel<<<blocksPerGrid, threadsPerBlock>>>(image, width, height);
    cudaDeviceSynchronize();
}
