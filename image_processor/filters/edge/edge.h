#pragma once

#include "../filter.h"

class FilterEdge : public Filter {
public:
    FilterEdge();

    explicit FilterEdge(double threshold);

    ~FilterEdge() override = default;

    void ApplyFilter(Picture& picture) override;

    int64_t Correct(double color) const;

private:
    double threshold_;
};
