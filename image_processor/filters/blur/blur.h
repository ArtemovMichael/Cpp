#pragma once

#include "../filter.h"

class FilterBlur : public Filter {
public:
    FilterBlur();

    explicit FilterBlur(double sigma);

    ~FilterBlur() override = default;

    void ApplyFilter(Picture& picture) override;

private:
    double sigma_;
};

struct TempColorValues {
    double red;
    double green;
    double blue;
};
