#pragma once

#include "direction.hpp"
#include "point.hpp"

class Point;

class BaseTransformStrategy {
public:
    virtual Point transform(const Point &p) = 0;
};


class MoveStrategy: public BaseTransformStrategy {
    double _x, _y, _z;
public:
    MoveStrategy(double x, double y, double z);
    virtual Point transform(const Point &p) override;
};

class ScaleStrategy: public BaseTransformStrategy {
    double _value;
public:
    ScaleStrategy(double value);
    virtual Point transform(const Point &p) override;
};


class RotateStrategy: public BaseTransformStrategy {
    Direction _dir;
    double _value;
public:
    RotateStrategy(Direction dir, double value);
    virtual Point transform(const Point &p) override;
};
