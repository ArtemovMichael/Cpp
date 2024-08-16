#include "crop.h"
#include <algorithm>

FilterCrop::FilterCrop(int32_t width, int32_t height) {
    width_ = width;
    height_ = height;
}

void FilterCrop::ApplyFilter(Picture &picture) {
    int32_t height = std::min(height_, picture.GetHeight());
    int32_t width = std::min(width_, picture.GetWidth());
    Pixels pixels = picture.GetPixels();

    std::reverse(pixels.begin(), pixels.end());
    pixels.resize(height);
    std::reverse(pixels.begin(), pixels.end());

    for (int32_t x = 0; x < picture.GetHeight(); x++) {
        pixels[x].resize(width);
    }

    picture.SetPixels(pixels);
    picture.SetHeight(height);
    picture.SetWidth(width);
}
