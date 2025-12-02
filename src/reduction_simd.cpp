#include "reduction.hpp"

float reduce_simd(const std::vector<float>& data) {
    float sum = 0.0f;

    // Let the compiler vectorize using OpenMP SIMD
    // #pragma omp simd reduction(+:sum)
    for (int i = 0; i < static_cast<int>(data.size()); ++i) {
        sum += data[i];
    }

    return sum;
}

// Fallback CPU implementations for CUDA variants so the code links on Windows
float reduce_cuda_naive(const std::vector<float>& data) {
    return reduce_simd(data);
}

float reduce_cuda_optimized(const std::vector<float>& data) {
    return reduce_simd(data);
}
