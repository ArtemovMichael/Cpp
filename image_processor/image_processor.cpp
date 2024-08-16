#include <vector>
#include <iostream>
#include "picture/picture.h"
#include "parsing/parser.h"
#include "filter_applier/filter_applier.h"

void WriteHelp() {
    std::cout << "\nСправка: \n"
                 "- neg: преобразует изображение в негатив.\n"
                 "- crop: обрезает изображение по заданной ширине и высоте.\n"
                 "- gs: преобразует изображение в оттенки серого.\n"
                 "- sharp: повышает резкость на изображении.\n"
                 "- edge: выделяет границы у изображения, параметр threshold.\n"
                 "- blur: Гауссово размытие, параметр sigma.\n"
                 "- mosaic: преобразует картинку в мозаику, параметр сторона квадрата.\n \n";
}

int main(int argc, const char** argv) {
    try {
        const char* path_in = argv[1];
        const char* path_out = argv[2];
        Picture picture(path_in);
        std::vector<Argument> arguments = Parse(argc, argv);
        for (Argument argument : arguments) {
            CreateFilter(argument)->ApplyFilter(picture);
        }
        picture.Write(path_out);
    } catch (std::exception& e) {
        WriteHelp();
        std::cout << e.what() << "\n";
    }
    return 0;
}
