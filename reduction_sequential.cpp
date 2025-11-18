#include "reduction.hpp"

float reduce_sequential(const std::vector<float>& data) {
    float sum = 0.0f;
    for (float x : data) {
        sum += x;
    }
    return sum;
}
