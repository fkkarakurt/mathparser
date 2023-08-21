#include "math_module.h"
#include <vector>
#include <stdexcept> 

std::vector<std::vector<double>> inverse2x2Matrix(const std::vector<std::vector<double>> &matrix)
{
    double determinant = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    if (determinant == 0)
    {
        // Tersi olmayan matris
        throw std::runtime_error("Determinant 0, matrisin tersi yok.");
    }

    std::vector<std::vector<double>> inverse = {
        {matrix[1][1] / determinant, -matrix[0][1] / determinant},
        {-matrix[1][0] / determinant, matrix[0][0] / determinant}};

    return inverse;
}
