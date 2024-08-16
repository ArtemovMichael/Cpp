#include "sharp.h"
#include "../apply_matrix/apply_matrix.h"

FilterSharp::FilterSharp() {
}

void FilterSharp::ApplyFilter(Picture& picture) {
    const std::vector<std::vector<double>> matrix = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
    ApplyMatrix(picture, matrix);
}
