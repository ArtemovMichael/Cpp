#pragma once

#include <fstream>
#include "../picture/picture.h"

class Filter {
public:
    virtual ~Filter() = default;

    virtual void ApplyFilter(Picture& picture) = 0;
};
