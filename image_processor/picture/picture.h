#pragma once

#include "pixel.h"
#include <vector>
#include <cstdint>

#pragma pack(push, 1)

struct Header {
    uint16_t file_type;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset_data;
};

struct InfoHeader {
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bits;
    uint32_t compression;
    uint32_t image_size;
    int32_t x_pixels_per_meter;
    int32_t y_pixels_per_meter;
    uint32_t n_colours;
    uint32_t important_colours;
};

#pragma pack(pop)

using Pixels = std::vector<std::vector<Pixel>>;

class Picture {
public:
    explicit Picture(const char *path_in);

    void Read(const char *path_in);

    void Write(const char *path_out);

    Pixels GetPixels() const;

    const Pixels &GetRefPixels() const;

    void SetPixel(int32_t x, int32_t y, const Pixel &pixel);

    void SetPixels(const Pixels &pixels);

    int32_t GetWidth() const;

    void SetWidth(int32_t new_width);

    int32_t GetHeight() const;

    void SetHeight(int32_t new_height);

    uint32_t CountOffset() const;

    bool operator==(const Picture &other) const;

    Picture(Header header, InfoHeader info_header, Pixels pixels);

private:
    Pixels pixels_;
    Header header_;
    InfoHeader info_header_;
};
