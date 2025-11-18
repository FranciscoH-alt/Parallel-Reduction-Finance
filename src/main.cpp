#include "reduction.hpp"

#include <iostream>
#include <string>
#include <cstdlib>

int main(int argc, char** argv) {
    // Default settings
    std::size_t n = 100000000; // 1e8 elements
    std::string variant_name = "seq";

    if (argc >= 2) {
        variant_name = argv[1];      // e.g., seq, omp, simd, cuda_naive, cuda_opt
    }
    if (argc >= 3) {
        n = std::strtoull(argv[2], nullptr, 10); // e.g., 50000000
    }

    std::cout << "Parallel Reduction Benchmark\n";
    std::cout << "Variant: " << variant_name << "\n";
    std::cout << "N      : " << n << "\n";

    Variant v;
    try {
        v = parse_variant(variant_name);
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        std::cerr << "Usage: " << argv[0] << " [seq|omp|simd|cuda_naive|cuda_opt] [N]\n";
        return 1;
    }

    auto data = generate_data(n, 1.0f);
    double elapsed_ms = 0.0;

    try {
        float result = run_reduction(v, data, elapsed_ms);
        std::cout << "Result : " << result << "\n";
        std::cout << "Time   : " << elapsed_ms << " ms\n";
        std::cout << "Throughput: " << (1e-6 * n / elapsed_ms) << " million elements/s\n";
    } catch (const std::exception& e) {
        std::cerr << "Error during reduction: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
