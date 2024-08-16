#pragma once

#include "../filter.h"

class FilterNegative : public Filter {
public:
    FilterNegative();

    ~FilterNegative() override = default;

    void ApplyFilter(Picture& picture) override;
};
