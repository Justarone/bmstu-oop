#pragma once

#include "transformator.hpp"
#include "drawer.hpp"
#include "proector.hpp"

class BaseDrawer;
class Component;
class Composite;
class ModelComponent;
class CameraComponent;

class BaseComponentVisitor {
public:
    virtual void visit(Composite &) const = 0;
    virtual void visit(CameraComponent &) const = 0;
    virtual void visit(ModelComponent &) const = 0;
};


class ScaleVisitor: public BaseComponentVisitor {
    double _value;
public:
    ScaleVisitor(double value);
    virtual void visit(Composite &) const override;
    virtual void visit(CameraComponent &) const override {};
    virtual void visit(ModelComponent &) const override;
};


class MoveVisitor: public BaseComponentVisitor {
    double _x, _y, _z;
public:
    MoveVisitor(double x, double y, double z);
    virtual void visit(Composite &) const override;
    virtual void visit(CameraComponent &) const override;
    virtual void visit(ModelComponent &) const override;
};


class RotateVisitor: public BaseComponentVisitor {
    Direction _dir;
    double _value;
public:
    RotateVisitor(Direction dir, double value);
    virtual void visit(Composite &) const override;
    virtual void visit(CameraComponent &) const override;
    virtual void visit(ModelComponent &) const override;
};

class DrawVisitor: public BaseComponentVisitor {
    shared_ptr<BaseDrawer> _drawer;
    shared_ptr<BaseCamera> _cam;
    shared_ptr<BaseProector> _proector;
public:
    DrawVisitor(shared_ptr<BaseDrawer> drawer, shared_ptr<BaseCamera> cam,
            shared_ptr<BaseProector> proector);
    virtual void visit(Composite &) const override;
    virtual void visit(CameraComponent &) const override;
    virtual void visit(ModelComponent &) const override;
};

#include "components.hpp"
