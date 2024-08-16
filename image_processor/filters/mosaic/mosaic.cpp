#include "mosaic.h"
#include <algorithm>

const int64_t MAX = 255;
const int64_t MIN = 0;

FilterMosaic::FilterMosaic(int32_t side) {
    side_ = side;
}

void FilterMosaic::ApplyFilter(Picture& picture) {
    int32_t height = picture.GetHeight();
    int32_t width = picture.GetWidth();
    Pixels ans(height, std::vector<Pixel>(width));
    const Pixels& pixels = picture.GetRefPixels();
    for (int32_t i = 0; i < height; i++) {
        for (int32_t j = 0; j < width; j++) {
            if (i % side_ == 0 && j % side_ == 0) {
                TempColorValues64 temporary_values{0, 0, 0};  // NOLINT
                int64_t cnt = 0;
                for (int32_t x = i; x < std::min(i + side_, height); x++) {
                    for (int32_t y = j; y < std::min(j + side_, width); y++) {

                        temporary_values.red += static_cast<int64_t>(pixels[x][y].red_);
                        temporary_values.green += static_cast<int64_t>(pixels[x][y].green_);
                        temporary_values.blue += static_cast<int64_t>(pixels[x][y].blue_);
                        cnt++;
                    }
                }
                temporary_values.red /= cnt;
                temporary_values.green /= cnt;
                temporary_values.blue /= cnt;
                for (int32_t x = i; x < std::min(i + side_, height); x++) {
                    for (int32_t y = j; y < std::min(j + side_, width); y++) {

                        uint8_t cur_red = static_cast<uint8_t>(std::clamp(temporary_values.red, MIN, MAX));
                        uint8_t cur_green = static_cast<uint8_t>(std::clamp(temporary_values.green, MIN, MAX));
                        uint8_t cur_blue = static_cast<uint8_t>(std::clamp(temporary_values.blue, MIN, MAX));

                        picture.SetPixel(y, x, Pixel(cur_blue, cur_green, cur_red));
                    }
                }
            }
        }
    }
}
