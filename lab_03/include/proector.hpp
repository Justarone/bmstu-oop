#pragma once

#include <cmath>

#include "point2d.hpp"
#include "camera.hpp"
#include "point.hpp"

class BaseProector {
public:
    virtual Point2d getProection(Point p, BaseCamera &cam) = 0;
};

class OrtogonalProector: public BaseProector { // works only with Camera obj
public:
    explicit OrtogonalProector();
    virtual Point2d getProection(Point p, BaseCamera &cam) override;
};
