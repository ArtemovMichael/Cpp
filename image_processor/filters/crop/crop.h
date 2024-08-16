#pragma once

#include "../filter.h"

class FilterCrop : public Filter {
public:
    FilterCrop();

    ~FilterCrop() override = default;

    FilterCrop(int32_t width, int32_t height);

    void ApplyFilter(Picture& picture) override;

private:
    int32_t width_;
    int32_t height_;
};
