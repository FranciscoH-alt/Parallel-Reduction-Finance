# Parallel Reduction – Finance Acceleration Project

This project implements multiple GPU-based and CPU-based parallel reduction strategies, originally built for exploring performance optimizations in financial computation workloads (e.g., summation, aggregation, Monte Carlo methods).

The repository includes:
- **Naive CUDA reduction**
- **Optimized CUDA reduction (shared memory + unrolling)**
- **CPU STL reduction**
- **Performance benchmarking framework**
- **CMake build system**

---

## 🔧 Requirements

This project uses CUDA + C++ and requires the following system packages:

### System requirements
- **CMake ≥ 3.22**
- **CUDA Toolkit ≥ 12.0**
- **NVIDIA Driver ≥ 525**
- **gcc/g++ ≥ 11**

### Optional (profiling)
- NVIDIA Nsight Systems
- NVIDIA Nsight Compute
- nvprof (deprecated but supported on older drivers)

You may install them using:

```bash
sudo apt install cmake gcc g++
