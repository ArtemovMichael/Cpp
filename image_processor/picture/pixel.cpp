#include "pixel.h"

Pixel::Pixel() : blue_(0), green_(0), red_(0) {
}

Pixel::Pixel(uint8_t blue, uint8_t green, uint8_t red) : blue_(blue), green_(green), red_(red) {
}

void Pixel::SetValue(uint8_t blue, uint8_t green, uint8_t red) {
    blue_ = blue;
    green_ = green;
    red_ = red;
}
