#include "proector.hpp"

Point2d OrtogonalProector::getProection(Point p, BaseCamera &camera) {
    Camera &cam = dynamic_cast<Camera &>(camera);
    double len = cam._nx * cam._nx + cam._ny * cam._ny + cam._nz * cam._nz;
    double XYProect = cam._nx * cam._nx + cam._ny * cam._ny;
    double angleZ = std::acos(sqrt(XYProect) / sqrt(len));
    double angleY = std::acos(sqrt(len - cam._nx * cam._nx) / sqrt(len));

    MatrixTransformator transformator;
    transformator.rotate(Direction::Z, angleZ);
    transformator.rotate(Direction::Y, angleY);
    transformator.move(-cam._x, -cam._y, -cam._z);
    p.transform(transformator);
    return Point2d(p.getX(), p.getY());
}

OrtogonalProector::OrtogonalProector() {};
