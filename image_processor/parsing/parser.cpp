#include "parser.h"
#include <stdexcept>
#include <fstream>

bool CheckIfPositiveNumber(const char* str) {
    char* endptr = nullptr;
    int64_t number = std::strtol(str, &endptr, 10);  // NOLINT
    return (*endptr == '\0' && number > 0);
}

bool CheckIfFloatingPointNumber(const char* str) {
    char* endptr = nullptr;
    std::strtod(str, &endptr);
    return (*endptr == '\0');
}

std::vector<Argument> Parse(int argc, const char** argv) {
    if (argc < 3) {
        throw std::invalid_argument("Недостаточно аргументов.");
    }

    std::vector<Argument> ans;

    for (int i = 3; i < argc; i++) {
        std::string argument = argv[i];
        if (argument == "-gs") {
            ans.push_back(Argument{FilterType::Grayscale, 0, 0, 0});
        } else if (argument == "-neg") {
            ans.push_back(Argument{FilterType::Negative, 0, 0, 0});
        } else if (argument == "-crop") {
            if (argc <= i + 2) {
                throw std::invalid_argument("Недостаточно аргументов для фильтра crop.");
            }
            if (!CheckIfPositiveNumber(argv[i + 1]) || !CheckIfPositiveNumber(argv[i + 2])) {
                throw std::invalid_argument("Переданы неверные аргументы для фильтра crop.");
            }
            ans.push_back(Argument{FilterType::Crop, std::atoi(argv[i + 1]), std::atoi(argv[i + 2]), 0});
            i += 2;
        } else if (argument == "-sharp") {
            ans.push_back(Argument{FilterType::Sharpening, 0, 0, 0});
        } else if (argument == "-edge") {
            if (argc <= i + 1) {
                throw std::invalid_argument("Недостаточно аргументов для фильтра edge.");
            }
            if (!CheckIfFloatingPointNumber(argv[i + 1])) {
                throw std::invalid_argument("Переданы неверные аргументы для фильтра edge.");
            }
            ans.push_back(Argument{FilterType::EdgeDetection, 0, 0, std::stod(argv[i + 1])});
            i++;
        } else if (argument == "-blur") {
            if (argc <= i + 1) {
                throw std::invalid_argument("Недостаточно аргументов для фильтра blur.");
            }
            if (!CheckIfFloatingPointNumber(argv[i + 1])) {
                throw std::invalid_argument("Переданы неверные аргументы для фильтра blur.");
            }
            ans.push_back(Argument{FilterType::GaussianBlur, 0, 0, std::stod(argv[i + 1])});
            i++;
        } else if (argument == "-mosaic") {
            if (argc <= i + 1) {
                throw std::invalid_argument("Недостаточно аргументов для фильтра mosaic.");
            }
            if (!CheckIfPositiveNumber(argv[i + 1])) {
                throw std::invalid_argument("Переданы неверные аргументы для фильтра mosaic.");
            }
            ans.push_back(Argument{FilterType::Mosaic, std::atoi(argv[i + 1]), 0, 0});
            i++;
        } else {
            throw std::invalid_argument("Есть неверный фильтр.");
        }
    }

    return ans;
}
