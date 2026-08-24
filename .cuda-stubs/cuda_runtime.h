#pragma once

#include <cstddef>

// Minimal declarations for editor/LSP support.
// LeetGPU provides the real CUDA runtime when the solution is submitted.

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
