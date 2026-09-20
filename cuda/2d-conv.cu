#include <cuda_runtime.h>

__global__ void k(const float *input, const float *kernel, float *output,
                  int input_rows, int input_cols, int kernel_rows,
                  int kernel_cols, int output_rows, int output_cols) {

    extern __shared__ float shared_kernel[];

    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int N = output_rows * output_cols;

    // Load kernel into shared memory by first threads
    for (int i = threadIdx.x; i < kernel_rows * kernel_cols; i += blockDim.x) {
        shared_kernel[i] = kernel[i];
    }
    __syncthreads();

    if (idx >= N)
        return;

    int rowId = idx / output_cols;
    int colId = idx % output_cols;

    float sum = 0.0f;
    for (int row = 0; row < kernel_rows; row++) {
        int curr_row = rowId + row;
        for (int col = 0; col < kernel_cols; col++) {
            int curr_col = colId + col;
            sum += shared_kernel[row * kernel_cols + col] *
                   input[curr_row * input_cols + curr_col];
        }
    }

    output[rowId * output_cols + colId] = sum;
}

// input, kernel, output are device pointers
extern "C" void solve(const float *input, const float *kernel, float *output,
                      int input_rows, int input_cols, int kernel_rows,
                      int kernel_cols) {

    int output_rows = input_rows - kernel_rows + 1;
    int output_cols = input_cols - kernel_cols + 1;

    int outputN = output_cols * output_rows;
    int threadsPerBlock = 256;
    int blocksPerGrid = (outputN + threadsPerBlock - 1) / threadsPerBlock;

    k<<<blocksPerGrid, threadsPerBlock,
        kernel_cols * kernel_rows * sizeof(float)>>>(
        input, kernel, output, input_rows, input_cols, kernel_rows, kernel_cols,
        output_rows, output_cols);
    cudaDeviceSynchronize();
}
