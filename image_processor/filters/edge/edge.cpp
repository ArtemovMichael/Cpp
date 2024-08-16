#include <memory>
#include "edge.h"
#include "../grayscale/grayscale.h"
#include "../apply_matrix/apply_matrix.h"

FilterEdge::FilterEdge(double threshold) {
    threshold_ = static_cast<double>(MAX) * threshold;
}

void FilterEdge::ApplyFilter(Picture& picture) {

    std::make_unique<FilterGrayscale>()->ApplyFilter(picture);

    const std::vector<std::vector<double>> matrix = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
    ApplyMatrix(picture, matrix);

    int32_t height = picture.GetHeight();
    int32_t width = picture.GetWidth();

    const Pixels& pixels = picture.GetRefPixels();

    for (int32_t x = 0; x < height; x++) {
        for (int32_t y = 0; y < width; y++) {
            Pixel current_pixel = pixels[x][y];

            uint8_t cur_color = current_pixel.red_ > static_cast<uint8_t>(threshold_) ? 255 : 0;  // NOLINT

            picture.SetPixel(y, x, Pixel(cur_color, cur_color, cur_color));
        }
    }
}
