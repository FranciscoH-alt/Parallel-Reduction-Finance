#include "reduction.hpp"

#include <stdexcept>
#include <iostream>

#ifdef HAVE_CUDA
// We will put real CUDA kernels here later.
#endif

float reduce_cuda_naive(const std::vector<float>&) {
#ifndef HAVE_CUDA
    throw std::runtime_error("CUDA not enabled. Configure with -DENABLE_CUDA=ON");
#else
    // TODO: implement naive GPU reduction
    std::cerr << "[WARN] reduce_cuda_naive is not implemented yet.\n";
    return 0.0f;
#endif
}

float reduce_cuda_optimized(const std::vector<float>&) {
#ifndef HAVE_CUDA
    throw std::runtime_error("CUDA not enabled. Configure with -DENABLE_CUDA=ON");
#else
    // TODO: implement optimized GPU reduction
    std::cerr << "[WARN] reduce_cuda_optimized is not implemented yet.\n";
    return 0.0f;
#endif
}
