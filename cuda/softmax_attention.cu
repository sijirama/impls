#include <cuda_runtime.h>
#include <math.h>

#define TILE_WIDTH 4;

__global__ void matmul(const float *A, const float *B, float *C, int M, int N,
                       int K, bool shouldSqrt) {

    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row > M || col > N)
        return;

    float sum = 0.0f;
    for (int k = 0; k < K; k++) {
        sum += A[row * K + k] * B[k * N + col];
    }

    C[row * N + col] = shouldSqrt ? sqrtf(sum) : sum;
}

__global__ void transpose(float *output, const float *K, int N, int d) {

    int x = blockIdx.x * blockDim.x + threadIdx.x;
    int y = blockIdx.y * blockDim.y + threadIdx.y;

    if (x < d && y < N) {
        output[y * N + x] = K[x * d + y];
    }
}

// Q, K, V, output are device pointers
extern "C" void solve(const float *Q, const float *K, const float *V,
                      float *output, int M, int N, int d) {

    // Matrix Q is of size M×d and matrices K and V are of size N×d

    // transpose K into K_t - K dim is N * D
    dim3 threadsPerBlock(16, 16);
    int numBlocksX = (d + threadsPerBlock.x - 1) / threadsPerBlock.x;
    int numBlocksY = (N + threadsPerBlock.y - 1) / threadsPerBlock.y;
    dim3 numBlocks(numBlocksX, numBlocksY);

    float *K_t = nullptr;
    size_t sizeInBytes = N * d * sizeof(float);
    cudaError_t err = cudaMalloc((void **)&K_t, sizeInBytes);
    transpose<<<numBlocks, threadsPerBlock>>>(K_t, K, N, d);

    // matmul Q and K_t
    float *A = nullptr;
    sizeInBytes = M * N * sizeof(float);
    err = cudaMalloc((void **)&A, sizeInBytes);

    // A (M * N) = Q (M * d) @ K_t (d * N) // MNK <=> MNd
    // el division by d ** 0.5 included
    dim3 threadsPerBlockMMA(16, 16);
    int numBlocksMMAX = (M + threadsPerBlockMMA.x - 1) / threadsPerBlockMMA.x;
    int numBlocksMMAY = (N + threadsPerBlockMMA.y - 1) / threadsPerBlockMMA.y;
    dim3 numBlocksMMA(numBlocksX, numBlocksY);
    matmul<<<numBlocksMMA, threadsPerBlockMMA>>>(Q, K_t, A, M, N, d, false);

    // row wise softmax into A
    float *O = nullptr;
    sizeInBytes = M * N * sizeof(float);
    err = cudaMalloc((void **)&O, sizeInBytes);
    // softmax kernel from A into O pls

    // matmul between A and v
    // output ( M * d) = O ( M * N ) * V ( N * d) // MdN
    matmul(O, V, output, M, d, N, false);
}
