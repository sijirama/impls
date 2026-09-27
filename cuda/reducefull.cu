#include <__clang_cuda_builtin_vars.h>
#include <cuda_runtime.h>

#define FULL_MASK 0xffffffff

__device__ float warpReduceSum(float val) {
    for (int offset = 16; offset > 0; offset /= 2) {
        val += __shfl_down_sync(FULL_MASK, val, offset);
    }
    return val;
}

__global__ void reduceFull(const float *input, float *output, int n) {

    extern __shared__ float temp[];

    // grid stride loop to first aggregate all values to work in the block
    float sum = 0.0f;
    for (int i = blockIdx.x * blockDim.x + threadIdx.x; i < n;
         i += gridDim.x * blockDim.x) {
        sum += input[i];
    }
    temp[threadIdx.x] = sum;

    __syncthreads();

    for (int stride = blockDim.x / 2; stride >= 32; stride >>= 1) {
        if (threadIdx.x < stride) {
            temp[threadIdx.x] += temp[threadIdx.x + stride];
        }
        __syncthreads();
    }

    if (threadIdx.x < 32) {
        float val = temp[threadIdx.x];

        val = warpReduceSum(val);

        if (threadIdx.x == 0)
            output[blockIdx.x] = val;
    }
}

void solve(const float *input, float *output, int n) {
    constexpr int BLOCK_SIZE = 256;

    // We deliberately use fewer blocks than "one thread per input element"
    // would require. Your kernel is expected to handle the remaining work
    // using thread coarsening / grid-stride processing.
    //
    // Cap the grid so large inputs do not simply create one thread for
    // every element.
    int num_blocks = (n + BLOCK_SIZE - 1) / BLOCK_SIZE;

    // Keep the exercise interesting: threads may need to process
    // multiple elements.
    if (num_blocks > 256)
        num_blocks = 256;

    reduceFull<<<num_blocks, BLOCK_SIZE, BLOCK_SIZE * sizeof(float)>>>(
        input, output, n);
}
