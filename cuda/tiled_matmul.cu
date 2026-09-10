

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

        // A = M x K | row x A_col
        int A_col = phase * TILE_WIDTH + threadIdx.x;
        A_shared[threadIdx.y][threadIdx.x] = A[row * K + A_col];

        // B = K x N | B_row x col
        int B_row = phase * TILE_WIDTH + threadIdx.y;
        B_shared[threadIdx.y][threadIdx.x] = B[B_row * N + col];

        __syncthreads();

        for (int k = 0; k < TILE_WIDTH; k++) {
            sum += A_shared[threadIdx.y][k] * B_shared[k][threadIdx.x];
        }

        __syncthreads();
    }

    C[row * N + col] = sum;
}
