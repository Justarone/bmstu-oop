#pragma once

#include "matrix.hpp"
#include "exception.hpp"
#include <cmath>

class Point;

enum class Direction { X, Y, Z };

class BaseTransformator {
public:
    virtual Point transform(const Point &p) = 0;
    virtual void move(double x, double y, double z) = 0;
    virtual void scale(double value) = 0;
    virtual void rotate(const Direction &dir, double value) = 0;
};


class MatrixTransformator: public BaseTransformator {
    Matrix<4, double> _transMatrix;
public:
    MatrixTransformator() = default;
    virtual Point transform(const Point &p) override;
    virtual void move(double x, double y, double z) override;
    virtual void scale(double value) override;
    virtual void rotate(const Direction &dir, double value) override;
};
