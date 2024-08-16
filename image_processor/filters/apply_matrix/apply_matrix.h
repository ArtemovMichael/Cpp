#pragma once

#include "../../picture/picture.h"

const int32_t MAX = 255;
const int32_t MIN = 0;

struct TempColorValues {
    int32_t red;
    int32_t green;
    int32_t blue;
};

void ApplyMatrix(Picture& picture, const std::vector<std::vector<double>>& matrix);
