// src/math_utils.cpp
#include "math_utils.h"

int32_t clamp(int32_t value, int32_t min, int32_t max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

uint32_t moving_average(uint32_t* buf, size_t len) {
    if (!buf || len == 0) return 0;
    uint64_t sum = 0;
    for (size_t i = 0; i < len; i++) sum += buf[i];
    return static_cast<uint32_t>(sum / len);
}