
#include <__clang_cuda_builtin_vars.h>
#include <cuda_runtime.h>

__global__ void k(const float *A, const float *B, float *result, int N) {

    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int tidx = threadIdx.x;

    __shared__ float temp[256];

    temp[tidx] = idx < N ? A[idx] * B[idx] : 0;
    __syncthreads();

    // addition reduction
    int stride = blockDim.x;
    for (; stride != 1;) {
        stride = stride / 2;
        if (threadIdx.x < stride) {
            temp[threadIdx.x] = temp[threadIdx.x] + temp[threadIdx.x + stride];
        }

        __syncthreads();
    }
    result[blockIdx.x] = temp[0];
}

__global__ void Add(float *k_output, float *result, int N) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int tidx = threadIdx.x;
    int stride = blockDim.x;

    __shared__ float temp[256];

    if (idx <= N) {
        temp[tidx] = temp[tidx] + temp[tidx + stride / 2];
    }
    __syncthreads();

    stride = stride / 2;

    for (; stride != 1;) {
    }
}

extern "C" void solve(const float *A, const float *B, float *result, int N) {
    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

    float *k_output = nullptr;
    cudaMalloc((void **)&k_output, N * sizeof(float));

    k<<<blocksPerGrid, threadsPerBlock>>>(A, B, k_output, N);
    cudaDeviceSynchronize();

    Add<<<blocksPerGrid, threadsPerBlock>>>(k_output, result, N);
    cudaDeviceSynchronize();
}
