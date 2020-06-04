#include "proector.hpp"

Point2d OrtogonalProector::getProection(Point p, shared_ptr<BaseCamera> camera) {
    Camera *cam = dynamic_cast<Camera *>(camera.get());
    double len = cam->_nx * cam->_nx + cam->_ny * cam->_ny + cam->_nz * cam->_nz;
    double XYProect = cam->_nx * cam->_nx + cam->_ny * cam->_ny;

    MatrixTransformator transformator;
    transformator.move(-cam->_x, -cam->_y, -cam->_z);

    if (std::fabs(cam->_nx) > std::numeric_limits<double>::epsilon()) {
        double angleZ = std::acos(sqrt(cam->_nx * cam->_nx) / sqrt(XYProect));
        transformator.rotate(Direction::Z, angleZ);
    }

    if (std::fabs(cam->_ny) > std::numeric_limits<double>::epsilon()) {
        double angleY = std::acos(sqrt(len - cam->_nz * cam->_nz) / sqrt(len));
        transformator.rotate(Direction::Y, angleY);
    }
    p.transform(transformator);
    return Point2d(p.getX(), p.getY());
}

OrtogonalProector::OrtogonalProector() {};
