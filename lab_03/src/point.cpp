#include "point.hpp"

void Point::transform(BaseTransformator &transformator) {
    Point res = transformator.transform(*this);
    _x = res._x, _y = res._y, _z = res._z; 
};
