#pragma once

#include <cstddef>

// Editor-only CUDA declarations. LeetGPU provides the real CUDA runtime when
// the solution is submitted; these are never used by the online judge.

#ifndef __global__
#define __global__
#endif

#ifndef __device__
#define __device__
#endif

#ifndef __host__
#define __host__
#endif

#ifndef __shared__
#define __shared__
#endif

using cudaError_t = int;

struct dim3 {
    unsigned int x;
    unsigned int y;
    unsigned int z;

    constexpr dim3(unsigned int x_value = 1,
                   unsigned int y_value = 1,
                   unsigned int z_value = 1)
        : x(x_value), y(y_value), z(z_value) {}
};

// CUDA built-in thread/block coordinates used by kernels.
extern const dim3 threadIdx;
extern const dim3 blockIdx;
extern const dim3 blockDim;
extern const dim3 gridDim;

enum cudaMemcpyKind {
    cudaMemcpyHostToHost,
    cudaMemcpyHostToDevice,
    cudaMemcpyDeviceToHost,
    cudaMemcpyDeviceToDevice,
};

inline cudaError_t cudaConfigureCall(dim3, dim3, std::size_t = 0, void* = nullptr) {
    return 0;
}

inline cudaError_t cudaSetupArgument(const void*, std::size_t, std::size_t) {
    return 0;
}

inline cudaError_t cudaLaunch(const void*) {
    return 0;
}

inline cudaError_t cudaDeviceSynchronize() {
    return 0;
}

inline cudaError_t cudaMalloc(void** address, std::size_t size) {
    (void)address;
    (void)size;
    return 0;
}

inline cudaError_t cudaFree(void* address) {
    (void)address;
    return 0;
}

inline cudaError_t cudaMemcpy(void* destination, const void* source,
                              std::size_t size, cudaMemcpyKind kind) {
    (void)destination;
    (void)source;
    (void)size;
    (void)kind;
    return 0;
}
