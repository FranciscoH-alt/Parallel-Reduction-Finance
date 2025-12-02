cmake_minimum_required(VERSION 3.18)
project(ParallelReduction LANGUAGES CXX)

# ---- Options ----
option(ENABLE_CUDA "Build CUDA implementations" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# High optimization by default
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# ---- OpenMP ----
find_package(OpenMP REQUIRED)

# ---- CUDA (optional) ----
if (ENABLE_CUDA)
    enable_language(CUDA)
    find_package(CUDAToolkit REQUIRED)
    add_definitions(-DHAVE_CUDA)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# ---- Sources ----
set(SOURCES
    src/main.cpp
    src/util.cpp
    src/reduction_sequential.cpp
    src/reduction_omp.cpp
    src/reduction_simd.cpp
)

if (ENABLE_CUDA)
    list(APPEND SOURCES src/reduction_cuda.cu)
endif()

add_executable(parallel_reduction ${SOURCES})

# Compile flags (you can tweak later)
target_compile_options(parallel_reduction PRIVATE
    /O2 /W4
)

# Link OpenMP
target_link_libraries(parallel_reduction PRIVATE OpenMP::OpenMP_CXX)

# Link CUDA if enabled
if (ENABLE_CUDA)
    target_link_libraries(parallel_reduction PRIVATE CUDA::cudart)
    set_target_properties(parallel_reduction PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON
    )
endif()
