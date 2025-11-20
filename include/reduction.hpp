#pragma once

#include <vector>
#include <string>
#include <cstddef>

// Which implementation to run
enum class Variant {
    Seq,        // Sequential
    Omp,        // OpenMP multithreaded
    Simd,       // OpenMP + SIMD
    CudaNaive,  // GPU naive (to be implemented)
    CudaOpt     // GPU optimized (to be implemented)
};

// Generate data
std::vector<float> generate_data(std::size_t n, float value = 1.0f);

// CPU reductions
float reduce_sequential(const std::vector<float>& data);
float reduce_omp(const std::vector<float>& data);
float reduce_simd(const std::vector<float>& data);

// GPU reductions (stubs for now)
float reduce_cuda_naive(const std::vector<float>& data);
float reduce_cuda_optimized(const std::vector<float>& data);

// Helper to run one variant and time it
float run_reduction(Variant v, const std::vector<float>& data, double& elapsed_ms);

// Parse CLI variant string -> enum
Variant parse_variant(const std::string& name);
