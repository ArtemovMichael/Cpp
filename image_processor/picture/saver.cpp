#include <fstream>
#include "picture.h"

void Picture::Write(const char *path_out) {
    std::ofstream output(path_out, std::ios_base::binary);
    if (!output) {
        throw std::invalid_argument("Невозможно открыть для записи файл.");
    }

    output.write(reinterpret_cast<const char *>(&header_), sizeof(header_));
    output.write(reinterpret_cast<const char *>(&info_header_), sizeof(info_header_));

    const uint32_t offset = CountOffset();

    int32_t height = info_header_.height;
    int32_t width = info_header_.width;

    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            output.write(reinterpret_cast<const char *>(&pixels_[y][x]), sizeof(Pixel));
        }
        output.seekp(offset, std::ios_base::cur);
    }
    output.close();
}
