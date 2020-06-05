#include "camera.hpp"

void Camera::move(double x, double y, double z) {
    _x += x, _y += y, _z += z;
}

void Camera::setPos(double x, double y, double z) {
    _x = x, _y = y, _z = z; 
}

void Camera::setNormal(double nx, double ny, double nz)  {
    _nx = nx, _ny = ny, _nz = nz; 
}

void Camera::rotate(double ax, double ay, double az) {
    Point p(_nx, _ny, _nz);

    shared_ptr<BaseTransformStrategy> strat1(new RotateStrategy(Direction::X, ax));
    shared_ptr<BaseTransformStrategy> strat2(new RotateStrategy(Direction::Y, ay));
    shared_ptr<BaseTransformStrategy> strat3(new RotateStrategy(Direction::Z, az));

    MyTransformator transformator(strat1);
    p.transform(transformator);
    transformator.setStrategy(strat2);
    p.transform(transformator);
    transformator.setStrategy(strat3);
    p.transform(transformator);

    _nx = p.getX(), _ny = p.getY(), _nz = p.getZ();
}

shared_ptr<BaseCamera> Camera::clone() {
    shared_ptr<BaseCamera> cam(new Camera(*this));
    return cam;
}
