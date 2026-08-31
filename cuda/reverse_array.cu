#include <cuda_runtime.h>

__global__ void reverse_array(float *input, int N) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx > N / 2)
        return;

    float t = input[idx];            // stoe the first cand
    input[idx] = input[N - 1 - idx]; // replace him with the latter cand
    input[N - 1 - idx] = t;          // replace the latter cand
}

// x,x,x,x,x,x,x

// 4
// 0 ... 3 = 0 ... N - 0 ? = 0 ... N - 1 - 0;
// 1 ... 2 = 1 ... N - 1 ? = 1 ... N - 1 - 1;

// 3
// 0 ... 2 = 0 ... N - 0 ? = 0 ... N - 1 - 0;
// 1 ... ? = 1 ... N - 1 ? = 1 ... N - 1 - 1;

// input is device pointer
extern "C" void solve(float *input, int N) {
    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

    reverse_array<<<blocksPerGrid, threadsPerBlock>>>(input, N);
    cudaDeviceSynchronize();
}
