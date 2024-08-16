#include "blur.h"
#include <cmath>
#include <algorithm>

const double MAX = 255;
const double MIN = 0;
const double THREE = 3;

FilterBlur::FilterBlur(double sigma) {
    sigma_ = fabs(std::ceil(sigma));
}

void FilterBlur::ApplyFilter(Picture& picture) {
    int32_t height = picture.GetHeight();
    int32_t width = picture.GetWidth();
    Pixels tmp_pixels(height, std::vector<Pixel>(width));
    int32_t delta = static_cast<int32_t>(THREE * sigma_);
    std::vector<double> coef;
    for (int i = 0; i < 2 * THREE * sigma_ + 1; i++) {
        coef.push_back(exp(-((i - 3 * sigma_) * (i - 3 * sigma_)) / (2 * (sigma_ * sigma_))));
    }

    double sum = 0;
    for (auto i : coef) {
        sum += i;
    }

    const Pixels& pixels = picture.GetRefPixels();
    for (int32_t i = 0; i < height; i++) {
        for (int32_t j = 0; j < width; j++) {

            TempColorValues temporary_values{0, 0, 0};  // NOLINT

            for (int32_t x = i - delta; x <= i + delta; x++) {

                int32_t pixel_x = std::clamp(j, 0, width - 1);
                int32_t pixel_y = std::clamp(x, 0, height - 1);
                Pixel pixel_to_check = pixels[pixel_y][pixel_x];

                temporary_values.red += static_cast<double>(pixel_to_check.red_ * coef[x - (i - delta)]);
                temporary_values.green += static_cast<double>(pixel_to_check.green_ * coef[x - (i - delta)]);
                temporary_values.blue += static_cast<double>(pixel_to_check.blue_ * coef[x - (i - delta)]);
            }
            temporary_values.red = temporary_values.red / sum;
            temporary_values.green = temporary_values.green / sum;
            temporary_values.blue = temporary_values.blue / sum;

            tmp_pixels[i][j].red_ = static_cast<uint8_t>(std::clamp(temporary_values.red, MIN, MAX));
            tmp_pixels[i][j].green_ = static_cast<uint8_t>(std::clamp(temporary_values.green, MIN, MAX));
            tmp_pixels[i][j].blue_ = static_cast<uint8_t>(std::clamp(temporary_values.blue, MIN, MAX));
        }
    }
    for (int32_t i = 0; i < height; i++) {
        for (int32_t j = 0; j < width; j++) {

            TempColorValues temporary_values{0, 0, 0};  // NOLINT

            for (int32_t x = j - delta; x <= j + delta; x++) {

                int32_t pixel_x = std::clamp(x, 0, width - 1);
                int32_t pixel_y = std::clamp(i, 0, height - 1);
                Pixel pixel_to_check = tmp_pixels[pixel_y][pixel_x];

                temporary_values.red += static_cast<double>(pixel_to_check.red_ * coef[x - (j - delta)]);
                temporary_values.green += static_cast<double>(pixel_to_check.green_ * coef[x - (j - delta)]);
                temporary_values.blue += static_cast<double>(pixel_to_check.blue_ * coef[x - (j - delta)]);
            }
            temporary_values.red = temporary_values.red / sum;
            temporary_values.green = temporary_values.green / sum;
            temporary_values.blue = temporary_values.blue / sum;

            uint8_t cur_red = static_cast<uint8_t>(std::clamp(temporary_values.red, MIN, MAX));
            uint8_t cur_green = static_cast<uint8_t>(std::clamp(temporary_values.green, MIN, MAX));
            uint8_t cur_blue = static_cast<uint8_t>(std::clamp(temporary_values.blue, MIN, MAX));

            picture.SetPixel(j, i, Pixel(cur_blue, cur_green, cur_red));
        }
    }
}
