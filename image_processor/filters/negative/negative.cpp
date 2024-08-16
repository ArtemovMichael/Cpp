#include "negative.h"

FilterNegative::FilterNegative() {
}

void FilterNegative::ApplyFilter(Picture& picture) {

    const Pixels& pixels = picture.GetRefPixels();

    for (int32_t i = 0; i < picture.GetHeight(); i++) {
        for (int32_t j = 0; j < picture.GetWidth(); j++) {
            picture.SetPixel(
                j, i, Pixel(255 - pixels[i][j].blue_, 255 - pixels[i][j].green_, 255 - pixels[i][j].red_));  // NOLINT
        }
    }
}
