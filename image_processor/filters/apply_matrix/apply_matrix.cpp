#include "apply_matrix.h"
#include <algorithm>

void ApplyMatrix(Picture& picture, const std::vector<std::vector<double>>& matrix) {
    int32_t height = picture.GetHeight();
    int32_t width = picture.GetWidth();

    const Pixels& pixels = picture.GetRefPixels();
    Pixels tmp_pixels(height, std::vector<Pixel>(width));

    for (int32_t x = 0; x < height; x++) {
        for (int32_t y = 0; y < width; y++) {

            TempColorValues temporary_values{0, 0, 0};  // NOLINT

            size_t matrix_x = 0;
            size_t matrix_y = 0;

            for (int32_t i = x - 1; i < x + 2; i++) {
                for (int32_t j = y - 1; j < y + 2; j++) {

                    int32_t pixel_x = std::clamp(j, 0, width - 1);
                    int32_t pixel_y = std::clamp(i, 0, height - 1);
                    Pixel pixel_to_check = pixels[pixel_y][pixel_x];

                    temporary_values.red += static_cast<int32_t>(matrix[matrix_y][matrix_x] * pixel_to_check.red_);
                    temporary_values.green += static_cast<int32_t>(matrix[matrix_y][matrix_x] * pixel_to_check.green_);
                    temporary_values.blue += static_cast<int32_t>(matrix[matrix_y][matrix_x] * pixel_to_check.blue_);

                    if (matrix_x != 2) {
                        matrix_x += 1;
                    } else {
                        matrix_x = 0;
                        matrix_y += 1;
                    }
                }
            }
            tmp_pixels[x][y].red_ = static_cast<uint8_t>(std::clamp(temporary_values.red, MIN, MAX));
            tmp_pixels[x][y].green_ = static_cast<uint8_t>(std::clamp(temporary_values.green, MIN, MAX));
            tmp_pixels[x][y].blue_ = static_cast<uint8_t>(std::clamp(temporary_values.blue, MIN, MAX));
        }
    }
    picture.SetPixels(tmp_pixels);
}
