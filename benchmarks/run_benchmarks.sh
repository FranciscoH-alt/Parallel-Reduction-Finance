#!/usr/bin/env bash
set -e

BIN=../build/parallel_reduction
N=100000000

echo "Running benchmarks with N=${N}"

for variant in seq omp simd; do
    echo "=== ${variant} ==="
    ${BIN} ${variant} ${N}
    echo
done
