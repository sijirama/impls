
#include <cuda_runtime.h>

#define TILE_WIDTH 4

__global__ void tiled_matmul(const float *A, const float *B, float *C, int M,
                             int N, int K) {

    int row = blockIdx.y * blockDim.y + threadIdx.y; // aross the grid
    int col = blockIdx.x * blockDim.x + threadIdx.x; // across the grid

    __shared__ float A_shared[2][TILE_WIDTH][TILE_WIDTH];
    __shared__ float B_shared[2][TILE_WIDTH][TILE_WIDTH];

    float sum = 0.0f;

    int phase = 0;

    __shared__ pipeline_shared_state<thread_scope_block, 2> pipeline_state;
    auto pipeline = make_pipeline(this_thread_block(), &pipeline_state);

    int A_col = phase * TILE_WIDTH + threadIdx.x;
    memcpy_async(
        &A_shared[phase][threadIdx.y][threadIdx.x], // destination: shared
        &A[row * K + A_col],                        // source: global
        sizeof(float),                              // number of bytes
        pipeline                                    // pipeline object
    );

    int B_row = phase * TILE_WIDTH + threadIdx.y;
    memcpy_async(&B_shared[phase][threadIdx.y][threadIdx.x], // destination
                 &B[B_row * N + col],                        // source
                 sizeof(float),                              // num of bytes
                 pipeline);

    int num_phases = (K + TILE_WIDTH - 1) / TILE_WIDTH;
    for (phase = 1; phase < num_phases; phase++) {

        pipeline.producer_acquire();
        int A_col = phase * TILE_WIDTH + threadIdx.x;
        memcpy_async(
            &A_shared[phase][threadIdx.y][threadIdx.x], // destination: shared
            &A[row * K + A_col],                        // source: global
            sizeof(float),                              // number of bytes
            pipeline                                    // pipeline object
        );

        int B_row = phase * TILE_WIDTH + threadIdx.y;
        memcpy_async(&B_shared[phase][threadIdx.y][threadIdx.x], // destination
                     &B[B_row * N + col],                        // source
                     sizeof(float),                              // num of bytes
                     pipeline);

        pipeline.producer_acquire();

        __syncthreads();

        for (int k = 0; k < TILE_WIDTH; k++) {
            sum += A_shared[phase][threadIdx.y][k] *
                   B_shared[phase][k][threadIdx.x];
        }

        __syncthreads();
    }
}
