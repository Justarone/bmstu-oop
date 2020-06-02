#pragma once

#include "point.hpp"
#include "transformator.hpp"

class OrtogonalProector;

class BaseCamera {
public:
    virtual void move(double x, double y, double z) = 0;
    virtual void setPos(double x, double y, double z) = 0;
    virtual void rotate(double ax, double ay, double az) = 0;
    virtual void setNormal(double ax, double ay, double az) = 0;
};


class Camera: public BaseCamera {
    friend OrtogonalProector;
protected:
    double _x, _y, _z;
    double _nx, _ny, _nz;

public:
    Camera(): _x(0), _y(0), _z(0), _nx(0), _ny(0), _nz(1.) {};
    Camera(double x, double y, double z): _x(x), _y(y), _z(z), _nx(0), _ny(0), _nz(1.) {};
    virtual void move(double x, double y, double z) override;
    virtual void setPos(double x, double y, double z) override;
    virtual void rotate(double ax, double ay, double az) override;
    virtual void setNormal(double nx, double ny, double nz) override;
};
