#pragma once

#include "../filter.h"

class FilterSharp : public Filter {
public:
    FilterSharp();

    ~FilterSharp() override = default;

    void ApplyFilter(Picture& picture) override;
};
