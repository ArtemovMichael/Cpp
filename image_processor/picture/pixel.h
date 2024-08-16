#pragma once
#include <cstdint>
#include <tuple>

struct Pixel {
    uint8_t blue_;
    uint8_t green_;
    uint8_t red_;

    Pixel();

    Pixel(uint8_t blue, uint8_t green, uint8_t red);

    void SetValue(uint8_t blue, uint8_t green, uint8_t red);

    bool operator==(const Pixel& rhs) const {
        return std::tie(blue_, green_, red_) == std::tie(rhs.blue_, rhs.green_, rhs.red_);
    }
};
