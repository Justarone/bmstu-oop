#include "transformator.hpp"
#include <limits>

Point MatrixTransformator::transform(const Point &p) {
    MathVec<4, double> resVec = { p.getX(), p.getY(), p.getZ() };
    resVec.mulLeft(_transMatrix);
    return Point(resVec.at(0), resVec.at(1), resVec.at(2));
}

void MatrixTransformator::move(double x, double y, double z) {
    Matrix<4, double> moveMatrix = { 0, 0, 0, 0,
                                     0, 0, 0, 0,
                                     0, 0, 0, 0,
                                     x, y, z, 1 };
    _transMatrix.mulRight(moveMatrix);
}

void MatrixTransformator::scale(double value) {
    if (std::abs(value) <= std::numeric_limits<double>::epsilon())
        throw AppValueException("Can't scale with 0 coeff");
    Matrix<4, double> scaleMatrix = { value, 0, 0, 0,
                                      0, value, 0, 0,
                                      0, 0, value, 0,
                                      0, 0, 0, 1 };
    _transMatrix.mulRight(scaleMatrix);
}

void MatrixTransformator::rotate(const Direction &dir, double value) {
    Matrix<4, double> rotateMatrix;
    if (dir == Direction::X) {
        rotateMatrix.at(1, 0) = cos(value);
        rotateMatrix.at(1, 1) = sin(value);
        rotateMatrix.at(2, 0) = -sin(value);
        rotateMatrix.at(2, 1) = cos(value);
    }
    else if (dir == Direction::Y) {
        rotateMatrix.at(0, 0) = -sin(value);
        rotateMatrix.at(0, 1) = cos(value);
        rotateMatrix.at(2, 0) = cos(value);
        rotateMatrix.at(2, 1) = sin(value);
    }
    else if (dir == Direction::Z) {
        rotateMatrix.at(0, 0) = cos(value);
        rotateMatrix.at(0, 1) = sin(value);
        rotateMatrix.at(1, 0) = -sin(value);
        rotateMatrix.at(1, 1) = cos(value);
    }

    _transMatrix.mulRight(rotateMatrix);
}
