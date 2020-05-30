#include "camera.hpp"

void Camera::rotate(double ax, double ay, double az) {
    Point p(_nx, _ny, _nz);

    MatrixTransformator transformator;
    transformator.rotate(Direction::X, ax);
    transformator.rotate(Direction::Y, ay);
    transformator.rotate(Direction::Z, az);

    p.transform(transformator);
    _nx = p.getX(), _ny = p.getY(), _nz = p.getZ();
}
