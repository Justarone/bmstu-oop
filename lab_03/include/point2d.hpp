#pragma once

class Point2d {
    double _x, _y;
public:
    Point2d(): _x(0), _y(0) {}
    Point2d(double x, double y): _x(x), _y(y) {}

    double getX() const { return _x; }
    double getY() const { return _y; }
    void setX(double value) { _x = value; }
    void setY(double value) { _y = value; }
};
