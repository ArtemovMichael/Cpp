#pragma once

#include "../filters/filter.h"

enum class FilterType { Crop, Grayscale, Negative, Sharpening, EdgeDetection, GaussianBlur, Mosaic };

struct Argument {
    FilterType filter;
    int32_t Param1;
    int32_t Param2;
    double DoubleParam;
};

std::vector<Argument> Parse(int argc, const char** argv);

bool CheckIfPositiveNumber(const char* str);

bool CheckIfFloatingPointNumber(const char* str);
