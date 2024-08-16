project(image_processor)

set(CMAKE_CXX_STANDARD 20)

add_executable(
    image_processor
    image_processor.cpp

    picture/pixel.cpp

    picture/picture.cpp

    parsing/parser.cpp

    picture/reader.cpp
    picture/saver.cpp

    filters/apply_matrix/apply_matrix.cpp

    filter_applier/filter_applier.cpp

    filters/negative/negative.cpp

    filters/grayscale/grayscale.cpp

    filters/crop/crop.cpp

    filters/sharp/sharp.cpp

    filters/edge/edge.cpp

    filters/blur/blur.cpp

    filters/mosaic/mosaic.cpp
)
