#include "filter_applier.h"

std::unique_ptr<Filter> CreateFilter(Argument argument) {
    switch (argument.filter) {
        case FilterType::Grayscale: {
            return std::make_unique<FilterGrayscale>();
        }
        case FilterType::Negative: {
            return std::make_unique<FilterNegative>();
        }
        case FilterType::Crop: {
            int32_t width = argument.Param1;
            int32_t height = argument.Param2;
            return std::make_unique<FilterCrop>(width, height);
        }
        case FilterType::Sharpening: {
            return std::make_unique<FilterSharp>();
        }
        case FilterType::EdgeDetection: {
            double threshold = argument.DoubleParam;
            return std::make_unique<FilterEdge>(threshold);
        }
        case FilterType::GaussianBlur: {
            double sigma = argument.DoubleParam;
            return std::make_unique<FilterBlur>(sigma);
        }
        case FilterType::Mosaic: {
            int32_t side = argument.Param1;
            return std::make_unique<FilterMosaic>(side);
        }
        default: {
            throw std::invalid_argument("Есть неверный фильтр.");
        }
    }
}
