cmake_minimum_required(VERSION 3.27.4)

project(unit_tests)

set(CMAKE_CXX_STANDARD 20)

add_library(
        contrib_catch_main
        ../../../../contrib/catch/catch_main.cpp
)

target_include_directories(
        contrib_catch_main
        PUBLIC ../../../../contrib/catch
)

add_executable(
    unit_tests
    unit_tests.cpp

    ../picture/pixel.cpp

    ../picture/picture.cpp

    ../parsing/parser.cpp

    ../picture/reader.cpp
    ../picture/saver.cpp

    ../filters/apply_matrix/apply_matrix.cpp

    ../filter_applier/filter_applier.cpp

    ../filters/negative/negative.cpp

    ../filters/grayscale/grayscale.cpp

    ../filters/crop/crop.cpp

    ../filters/sharp/sharp.cpp

    ../filters/edge/edge.cpp

    ../filters/blur/blur.cpp

    ../filters/mosaic/mosaic.cpp
)

target_link_libraries(
        unit_tests
        contrib_catch_main
)
