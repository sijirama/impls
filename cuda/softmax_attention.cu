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

// Warp-level reduction helper for finding the maximum value
__device__ __forceinline__ float warpReduceMax(float val) {
    for (int offset = warpSize / 2; offset > 0; offset /= 2) {
        val = fmaxf(val, __shfl_down_sync(0xffffffff, val, offset));
    }
    return val;
}

// Warp-level reduction helper for summing values
__device__ __forceinline__ float warpReduceSum(float val) {
    for (int offset = warpSize / 2; offset > 0; offset /= 2) {
        val += __shfl_down_sync(0xffffffff, val, offset);
    }
    return val;
}

__global__ void row_wise_softmax_kernel(const float *__restrict__ input,
                                        float *__restrict__ output,
                                        int num_cols) {

    int row = blockIdx.x;            // which row does this BLOCK own?
    int tid = threadIdx.x;           // which thread am I in the block?
    int lane = tid % 32;             // which lane am I in my warp?
    int warp_id = tid / 32;          // which warp am I in?
    int num_warps = blockDim.x / 32; // how many warps are in this block?

    extern __shared__ float shared_mem[];

    // points to the first element of the row this block owns.
    const float *row_in = input + row * num_cols;

    // points to the first element of the corresponding output row.
    float *row_out = output + row * num_cols;

    float local_max = -INFINITY;
    for (int col = tid; col < num_cols; col += blockDim.x) {
        local_max = fmaxf(local_max, row_in[col]);
    }

    local_max = warpReduceMax(local_max);

    if (lane == 0)
        shared_mem[warp_id] = local_max;

    __syncthreads();

    float row_max = (tid < num_warps) ? shared_mem[tid] : -INFINITY;
    if (warp_id == 0) {
        row_max = warpReduceMax(row_max);
        if (lane == 0)
            shared_mem[0] = row_max;
        // shared_mem[0] now holds the true row maximum
    }
    __syncthreads();

    row_max = shared_mem[0];

    // --- PASS 2: Compute Exponentials & Sum (Denominator) ---
    float local_sum = 0.0f;

    for (int col = tid; col < num_cols; col += blockDim.x) {
        local_sum += expf(row_in[col] - row_max);
    }

    local_sum = warpReduceMax(local_sum);

    if (lane == 0)
        shared_mem[warp_id] = local_sum;

    __syncthreads();

    float row_sum = (tid < num_warps) ? shared_mem[tid] : 0.0f;
    if (warp_id == 0) {
        row_sum = warpReduceSum(row_sum);

        if (lane == 0)
            shared_mem[0] = row_sum;
    }
    __syncthreads();

    row_sum = shared_mem[0];

    // --- PASS 3: Normalize and Write Output ---
    for (int col = tid; col < num_cols; col += blockDim.x) {
        row_out[col] = expf(row_in[col] - row_max) / row_sum;
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

    cudaDeviceSynchronize();

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
    matmul<<<numBlocksMMA, threadsPerBlockMMA>>>(Q, K_t, A, M, N, d, true);

    cudaDeviceSynchronize();

    // row wise softmax into O from A
    float *O = nullptr;
    sizeInBytes = M * N * sizeof(float);
    err = cudaMalloc((void **)&O, sizeInBytes);

    // softmax kernel from A into O pls
    int threadsPerBlockSoftmax = 256;
    int sizeOfBytesSharedMem = (threadsPerBlockSoftmax / 32) & sizeof(float);
    row_wise_softmax_kernel<<<M, threadsPerBlockSoftmax,
                              sizeOfBytesSharedMem>>>(A, O, N);

    cudaDeviceSynchronize();

    // matmul between A and v
    // output ( M * d) = O ( M * N ) * V ( N * d) // MdN
    matmul(O, V, output, M, d, N, false);

    cudaDeviceSynchronize();
}
