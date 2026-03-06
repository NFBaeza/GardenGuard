// src/math_utils.h
#pragma once
#include <cstdint>
#include <cstddef>

int32_t clamp(int32_t value, int32_t min, int32_t max);
uint32_t moving_average(uint32_t* buf, size_t len);