#include "transformator.hpp"
#include "point.hpp"

Point MatrixTransformator::transform(const Point &p) {
    MathVec<4, double> resVec = { p.getX(), p.getY(), p.getZ(), 1 };
    //std::cout << "Matrix:\n";
    //for (size_t i = 0; i < 4; i++) {
        //for (size_t j = 0; j < 4; j++)
            //std::cout << _transMatrix.at(i, j) << " ";
        //std::cout << std::endl;
    //}
    //std::cout << "Vector: \n";
    //for (size_t i = 0; i < 4; i++)
        //std::cout << resVec.at(i) << " ";
    //std::cout << std::endl;

    resVec.mulLeft(_transMatrix);
    //std::cout << "Vector after:\n";
    //for (size_t i = 0; i < 4; i++)
        //std::cout << resVec.at(i) << " ";

    return Point(resVec.at(0), resVec.at(1), resVec.at(2));
}

void MatrixTransformator::move(double x, double y, double z) {
    Matrix<4, double> moveMatrix = { 1, 0, 0, 0,
                                     0, 1, 0, 0,
                                     0, 0, 1, 0,
                                     x, y, z, 1 };

    std::cout << "Matrix before move:\n";
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++)
            std::cout << _transMatrix.at(i, j) << " ";
        std::cout << std::endl;
    }
    std::cout << "move matrix:\n";
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++)
            std::cout << _transMatrix.at(i, j) << " ";
        std::cout << std::endl;
    }
    
    _transMatrix.mulRight(moveMatrix);
    std::cout << "Matrix after move:\n";
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++)
            std::cout << _transMatrix.at(i, j) << " ";
        std::cout << std::endl;
    }
}

void MatrixTransformator::scale(double value) {
    if (std::abs(value) <= std::numeric_limits<double>::epsilon())
        throw AppValueException("Can't scale with 0 coeff");
    Matrix<4, double> scaleMatrix = { value, 0, 0, 0,
                                      0, value, 0, 0,
                                      0, 0, value, 0,
                                      0, 0, 0, 1 };
    std::cout << "Matrix before scale:\n";
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++)
            std::cout << _transMatrix.at(i, j) << " ";
        std::cout << std::endl;
    }
    _transMatrix.mulRight(scaleMatrix);
    std::cout << "Matrix after scale:\n";
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++)
            std::cout << _transMatrix.at(i, j) << " ";
        std::cout << std::endl;
    }
}

void MatrixTransformator::rotate(const Direction &dir, double value) {
    Matrix<4, double> rotateMatrix;

    if (dir == Direction::X) {
        rotateMatrix.at(0, 0) = 1;
        rotateMatrix.at(2, 1) = -sin(value);
        rotateMatrix.at(1, 1) = cos(value);
        rotateMatrix.at(1, 2) = sin(value);
        rotateMatrix.at(2, 2) = cos(value);
    }
    else if (dir == Direction::Y) {
        rotateMatrix.at(1, 1) = 1;
        rotateMatrix.at(0, 0) = cos(value);
        rotateMatrix.at(0, 2) = sin(value);
        rotateMatrix.at(2, 0) = -sin(value);
        rotateMatrix.at(2, 2) = cos(value);
    }
    else if (dir == Direction::Z) {
        rotateMatrix.at(2, 2) = 1;
        rotateMatrix.at(0, 0) = cos(value);
        rotateMatrix.at(0, 1) = sin(value);
        rotateMatrix.at(1, 0) = -sin(value);
        rotateMatrix.at(1, 1) = cos(value);
    }
    std::cout << "Matrix before rotate:\n";
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++)
            std::cout << _transMatrix.at(i, j) << " ";
        std::cout << std::endl;
    }

    _transMatrix.mulRight(rotateMatrix);

    std::cout << "Matrix after rotate:\n";
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++)
            std::cout << _transMatrix.at(i, j) << " ";
        std::cout << std::endl;
    }
}
