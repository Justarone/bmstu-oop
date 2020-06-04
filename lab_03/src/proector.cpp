#include "proector.hpp"

Point2d OrtogonalProector::getProection(Point p, shared_ptr<BaseCamera> camera) {
    std::cout << "Got: " << p.getX() << ", " << p.getY() << ", " << p.getZ() << std::endl;
    double a = p.getX(), b = p.getY();
    Camera *cam = dynamic_cast<Camera *>(camera.get());
    double len = cam->_nx * cam->_nx + cam->_ny * cam->_ny + cam->_nz * cam->_nz;
    double XYProect = cam->_nx * cam->_nx + cam->_ny * cam->_ny;
    double angleZ = std::acos(sqrt(XYProect) / sqrt(len));
    double angleY = std::acos(sqrt(len - cam->_nx * cam->_nx) / sqrt(len));

    MatrixTransformator transformator;
    transformator.move(-cam->_x, -cam->_y, -cam->_z);
    transformator.rotate(Direction::Z, angleZ);
    transformator.rotate(Direction::Y, angleY);
    p.transform(transformator);
    std::cout << "After Transformation: " << p.getX() << ", " << p.getY() << ", " << p.getZ() << std::endl;
    return Point2d(a, b);
    //return Point2d(p.getX(), p.getY());
}

OrtogonalProector::OrtogonalProector() {};
