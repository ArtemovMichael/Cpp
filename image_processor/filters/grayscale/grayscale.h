#pragma once

#include "../filter.h"

class FilterGrayscale : public Filter {
public:
    FilterGrayscale();

    ~FilterGrayscale() override = default;

    void ApplyFilter(Picture& picture) override;
};
