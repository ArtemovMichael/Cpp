#pragma once

#include "../filter.h"

class FilterMosaic : public Filter {
public:
    FilterMosaic();

    explicit FilterMosaic(int32_t side);

    ~FilterMosaic() override = default;

    void ApplyFilter(Picture& picture) override;

private:
    int32_t side_;
};

struct TempColorValues64 {
    int64_t red;
    int64_t green;
    int64_t blue;
};
