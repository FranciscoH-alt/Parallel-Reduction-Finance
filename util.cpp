#include "reduction.hpp"

#include <random>
#include <chrono>
#include <stdexcept>
#include <iostream>
#include <string>

std::vector<float> generate_data(std::size_t n, float value) {
    std::vector<float> data(n, value);
    // Later you can switch to random values if needed
    return data;
}

Variant parse_variant(const std::string& name) {
    if (name == "seq")   return Variant::Seq;
    if (name == "omp")   return Variant::Omp;
    if (name == "simd")  return Variant::Simd;
    if (name == "cuda_naive") return Variant::CudaNaive;
    if (name == "cuda_opt")   return Variant::CudaOpt;
    throw std::runtime_error("Unknown variant: " + name);
}

float run_reduction(Variant v, const std::vector<float>& data, double& elapsed_ms) {
    using clock = std::chrono::high_resolution_clock;

    auto start = clock::now();
    float result = 0.0f;

    switch (v) {
        case Variant::Seq:
            result = reduce_sequential(data);
            break;
        case Variant::Omp:
            result = reduce_omp(data);
            break;
        case Variant::Simd:
            result = reduce_simd(data);
            break;
        case Variant::CudaNaive:
            result = reduce_cuda_naive(data);
            break;
        case Variant::CudaOpt:
            result = reduce_cuda_optimized(data);
            break;
    }

    auto end = clock::now();
    elapsed_ms = std::chrono::duration<double, std::milli>(end - start).count();
    return result;
}
