#include "grayscale.h"

FilterGrayscale::FilterGrayscale() {
}

void FilterGrayscale::ApplyFilter(Picture& picture) {
    const Pixels& pixels = picture.GetRefPixels();

    for (int32_t i = 0; i < picture.GetHeight(); i++) {
        for (int32_t j = 0; j < picture.GetWidth(); j++) {
            uint8_t val =
                0.299 * pixels[i][j].red_ + 0.587 * pixels[i][j].green_ + 0.114 * pixels[i][j].blue_;  // NOLINT
            picture.SetPixel(j, i, Pixel(val, val, val));
        }
    }
}
