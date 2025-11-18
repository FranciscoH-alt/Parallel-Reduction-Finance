#include "reduction.hpp"

float reduce_simd(const std::vector<float>& data) {
    float sum = 0.0f;

    // Let the compiler vectorize using OpenMP SIMD
    #pragma omp simd reduction(+:sum)
    for (std::size_t i = 0; i < data.size(); ++i) {
        sum += data[i];
    }

    return sum;
}
