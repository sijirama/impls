

#include "cuda_runtime.h"
#define TILE_WIDTH 4

__global__ void tiled_matmul(const float *A, const float *B, float *C, int M,
                             int N, int K) {

    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    __shared__ float A_shared[TILE_WIDTH][TILE_WIDTH];
    __shared__ float B_shared[TILE_WIDTH][TILE_WIDTH];

    float sum = 0.0f;

    for (int phase = 0; phase < K / TILE_WIDTH; phase++) {

        A_shared[threadIdx.y][threadIdx.x] = A[row * K + col];
        B_shared[threadIdx.y][threadIdx.x] = B[col * K + row];

        __syncthreads();

        for (int k = 0; k < K; k++) {
            sum += A_shared[threadIdx.x][k] * B_shared[k][threadIdx.y];
        }

        __syncthreads();
    }

    C[row * K + col] = sum;
}
