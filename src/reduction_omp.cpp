#include "reduction.hpp"
#include <omp.h>

float reduce_omp(const std::vector<float>& data) {
    float sum = 0.0f;

    // Simple OpenMP parallel reduction baseline
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < static_cast<int>(data.size()); ++i) {
        sum += data[i];
    }

    return sum;
}
