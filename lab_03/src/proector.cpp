#include "proector.hpp"

Point2d OrtogonalProector::getProection(Point p, shared_ptr<BaseCamera> camera) {
    Camera *cam = dynamic_cast<Camera *>(camera.get());
    double len = cam->_nx * cam->_nx + cam->_ny * cam->_ny + cam->_nz * cam->_nz;
    double XYProect = cam->_nx * cam->_nx + cam->_ny * cam->_ny;

    shared_ptr<BaseTransformStrategy> moveStrat(new MoveStrategy(-cam->_x, -cam->_y, -cam->_z));
    MyTransformator transformator(moveStrat);
    p.transform(transformator);

    if (std::fabs(cam->_nx) > std::numeric_limits<double>::epsilon()) {
        double angleZ = std::acos(sqrt(cam->_nx * cam->_nx) / sqrt(XYProect));
        shared_ptr<BaseTransformStrategy> rotateStrategy1(new RotateStrategy(Direction::Z, angleZ));
        transformator.setStrategy(rotateStrategy1);
        p.transform(transformator);
    }

    if (std::fabs(cam->_ny) > std::numeric_limits<double>::epsilon()) {
        double angleY = std::acos(sqrt(len - cam->_nz * cam->_nz) / sqrt(len));
        shared_ptr<BaseTransformStrategy> rotateStrategy2(new RotateStrategy(Direction::Y, angleY));
        transformator.setStrategy(rotateStrategy2);
        p.transform(transformator);
    }

    return Point2d(p.getX(), p.getY());
}

OrtogonalProector::OrtogonalProector() {};
