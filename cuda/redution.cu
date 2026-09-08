
#include <cuda_runtime.h>

__global__ void reduction(const float *input, float *output, int N) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    int stride = blockDim.x;

    __shared__ temp[blockDim.x];

    if (idx < N) {
        temp[threadIdx.x] = input[idx];
    }

    if (gridDim.x[gridDim.x - 1] == blockIdx.x && idx > N - 1) {
        temp[(idx / blockIdx.x) - blockDim.x] = 0;
    }
    __syncthreads();

    for (; stride != 1;) {
        stride = stride / 2;

        if (threadIdx.x < stride) {
            temp[threadIdx.x] = temp[threadIdx.x] + temp[threadIdx.x + stride];
        }

        __syncthreads();
    }

    output[blockIdx.x] = temp[0]
}

// input, output are device pointers
extern "C" void solve(const float *input, float *output, int N) {

    int threadPerBlock = 256;
    int blockPerGrid = (N + threadPerBlock - 1) / threadPerBlock;

    float *d_gridOutput = nullptr;
    cudaMalloc((void **)&d_gridOutput, N * sizeof(float));

    reduction<<<blockPerGrid, threadPerBlock>>>(input, d_gridOutput, N);
    cudaDeviceSynchronize();

    // Fix 2: Allocate temporary CPU memory to pull data back from GPU
    float *h_gridOutput = (float *)malloc(N * sizeof(float));
    cudaMemcpy(h_gridOutput, d_gridOutput, N * sizeof(float),
               cudaMemcpyDeviceToHost);

    float total_sum = 0.0f;
    for (int i = 0; i < blockPerGrid; i++) {
        total_sum += h_gridOutput[i];
    }

    cudaMemcpy(output, &total_sum, sizeof(float), cudaMemcpyHostToDevice);

    // Fix 6: Free both GPU and CPU allocations
    cudaFree(d_gridOutput);
    free(h_gridOutput);
}
