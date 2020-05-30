#pragma once

#include "transformator.hpp"
class Composite;
class CameraComponent;
class ModelComponent;

class BaseComponentVisitor {
public:
    virtual void visit(Composite &) const = 0;
    virtual void visit(CameraComponent &) const = 0;
    virtual void visit(ModelComponent &) const = 0;
};


class ScaleVisitor: public BaseComponentVisitor {
    double _value;
public:
    ScaleVisitor(double value): _value(value) {}
    virtual void visit(Composite &) const override;
    virtual void visit(CameraComponent &) const override {};
    virtual void visit(ModelComponent &) const override;
};


class MoveVisitor: public BaseComponentVisitor {
    double _x, _y, _z;
public:
    MoveVisitor(double x, double y, double z): _x(x), _y(y), _z(z) {}
    virtual void visit(Composite &) const override;
    virtual void visit(CameraComponent &) const override;
    virtual void visit(ModelComponent &) const override;
};


class RotateVisitor: public BaseComponentVisitor {
    Direction _dir;
    double _value;
public:
    RotateVisitor(Direction dir, double value): _dir(dir), _value(value) {};
    virtual void visit(Composite &) const override;
    virtual void visit(CameraComponent &) const override;
    virtual void visit(ModelComponent &) const override;
};

#include "components.hpp"
