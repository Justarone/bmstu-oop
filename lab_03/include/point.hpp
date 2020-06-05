#pragma once

#include "transformator.hpp"

class BaseTransformator;

class Point {
    double _x, _y, _z;
public:
    Point() = default;
    Point(double x, double y, double z): _x(x), _y(y), _z(z) {};
    Point(const Point &) = default;
    Point &operator=(const Point &) = default;
    void transform(BaseTransformator &transformator);
    double getX() const { return _x; }
    double getY() const { return _y; }
    double getZ() const { return _z; }
};
