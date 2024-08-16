#include <fstream>
#include "picture.h"

void Picture::Read(const char *path_in) {

    std::ifstream input(path_in, std::ios_base::binary);
    if (!input) {
        throw std::invalid_argument("Невозможно прочесть файл.");
    }

    input.read(reinterpret_cast<char *>(&header_), sizeof(header_));
    const uint16_t valid_file_format = 0x4D42;
    if (header_.file_type != valid_file_format) {
        throw std::invalid_argument("Формат файла не bmp.");
    }

    input.read(reinterpret_cast<char *>(&info_header_), sizeof(info_header_));
    const uint16_t valid_bits = 24;
    if (info_header_.bits != valid_bits) {
        throw std::invalid_argument("Формат файла не распознан.");
    }

    input.seekg(header_.offset_data, input.beg);

    const uint32_t offset = CountOffset();

    for (int32_t i = 0; i < info_header_.height; i++) {
        std::vector<Pixel> line;
        for (int32_t j = 0; j < info_header_.width; j++) {
            Pixel pixel;
            input.read(reinterpret_cast<char *>(&pixel), sizeof(pixel));
            line.push_back(pixel);
        }
        pixels_.push_back(line);
        input.seekg(offset, input.cur);
    }
}
