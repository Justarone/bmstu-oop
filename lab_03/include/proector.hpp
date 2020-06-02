#pragma once

#include <cmath>

#include "point2d.hpp"
#include "camera.hpp"
#include "point.hpp"

class BaseProector {
public:
    virtual Point2d getProection(Point p) = 0;
};


class OrtogonalProector: public BaseProector { // works only with Camera obj
    Camera _cam;
public:
    explicit OrtogonalProector(const Camera &cam): _cam(cam) {}
    virtual Point2d getProection(Point p) override;
};
