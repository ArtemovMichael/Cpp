#include "picture.h"
#include <fstream>
#include <tuple>

Picture::Picture(const char *path_in) {
    Read(path_in);
}

Pixels Picture::GetPixels() const {
    return pixels_;
}

const Pixels &Picture::GetRefPixels() const {
    return pixels_;
}

void Picture::SetPixel(int32_t x, int32_t y, const Pixel &pixel) {
    pixels_[y][x] = pixel;
}

void Picture::SetPixels(const Pixels &pixels) {
    pixels_ = pixels;
}

int32_t Picture::GetWidth() const {
    return info_header_.width;
}

void Picture::SetWidth(int32_t new_width) {
    info_header_.width = new_width;
}

int32_t Picture::GetHeight() const {
    return info_header_.height;
}

void Picture::SetHeight(int32_t new_height) {
    info_header_.height = new_height;
}

uint32_t Picture::CountOffset() const {
    return (4 - info_header_.width * 3 % 4) % 4;  // NOLINT
}

bool Picture::operator==(const Picture &other) const {
    return std::tie(pixels_) == std::tie(other.pixels_);
}

Picture::Picture(Header header, InfoHeader info_header, Pixels pixels) {
    header_ = header;
    info_header_ = info_header;
    pixels_ = pixels;
}
