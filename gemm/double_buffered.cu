#include <cuda/pipeline>
#include <cuda_runtime.h>

#define TILE_WIDTH 4

__global__ void tiled_matmul(const float *A, const float *B, float *C, int M,
                             int N, int K) {

    int row = blockIdx.y * blockDim.y + threadIdx.y; // aross the grid
    int col = blockIdx.x * blockDim.x + threadIdx.x; // across the grid

    __shared__ float A_shared[2][TILE_WIDTH][TILE_WIDTH];
    __shared__ float B_shared[2][TILE_WIDTH][TILE_WIDTH];

    float sum = 0.0f;

    // prologue
    int phase = 0;
    int A_col = phase * TILE_WIDTH + threadIdx.x;
    cuda::memcpy_async(A_shared[0][threadIdx.y][threadIdx.x],
                       A[row * K + A_col], sizeof(float));

    int B_row = phase * TILE_WIDTH + threadIdx.y;
    cuda::memcpy_async(B_shared[0][threadIdx.y][threadIdx.x],
                       B[B_row * N + col], sizeof(float));

    for (int phase = 0; phase < K / TILE_WIDTH; phase++) {

        int current_stage = phase % 2;
        int next_stage = (phase + 1) % 2;

        pipeline_acquire();

        int A_col = phase * TILE_WIDTH + threadIdx.x;
        cuda::memcpy_async(A_shared[next_stage][threadIdx.y][threadIdx.x],
                           A[row * K + A_col], sizeof(float));

        int B_row = phase * TILE_WIDTH + threadIdx.y;
        cuda::memcpy_async(B_shared[next_stage][threadIdx.y][threadIdx.x],
                           B[B_row * N + col], sizeof(float));

        pipeline_commit();

        __syncthreads();

        consumer_wait();

        for (int k = 0; k < TILE_WIDTH; k++) {
            sum += A_shared[current_stage][threadIdx.y][k] *
                   B_shared[current_stage][k][threadIdx.x];
        }

        consumer_release();

        __syncthreads();
    }

    C[row * N + col] = sum;
}
