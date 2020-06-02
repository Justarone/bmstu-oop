#include "proector.hpp"

Point2d OrtogonalProector::getProection(Point p) {
    double len = _cam._nx * _cam._nx + _cam._ny * _cam._ny + _cam._nz * _cam._nz;
    double XYProect = _cam._nx * _cam._nx + _cam._ny * _cam._ny;
    double angleZ = std::acos(sqrt(XYProect) / sqrt(len));
    double angleY = std::acos(sqrt(len - _cam._nx * _cam._nx) / sqrt(len));

    MatrixTransformator transformator;
    transformator.rotate(Direction::Z, angleZ);
    transformator.rotate(Direction::Y, angleY);
    transformator.move(_cam._x, _cam._y, _cam._z);
    p.transform(transformator);
    return Point2d(p.getX(), p.getY());
}
