#pragma once

#include "transformator.hpp"

class Point {
    double _x, _y, _z;
public:
    Point(double x, double y, double z): _x(x), _y(y), _z(z) {};
    void transform(BaseTransformator &transformator) {
        Point res = transformator.transform(*this);
        _x = res._x, _y = res._y, _z = res._z; 

    };
    double getX() const { return _x; }
    double getY() const { return _y; }
    double getZ() const { return _z; }
};
