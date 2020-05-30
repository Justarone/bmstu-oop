#include "visitor.hpp"

void ScaleVisitor::visit(Composite &composite) const {
    for (auto &elem: composite) {
        if (elem->isComposite())
            visit(*static_cast<Composite *>(elem.get()));
        else if (elem->isVisible())
            visit(*static_cast<ModelComponent *>(elem.get()));
        else
            visit(*static_cast<CameraComponent *>(elem.get()));
    }
}


void RotateVisitor::visit(Composite &composite) const {
    for (auto &elem: composite) {
        if (elem->isComposite())
            visit(*static_cast<Composite *>(elem.get()));
        else if (elem->isVisible())
            visit(*static_cast<ModelComponent *>(elem.get()));
        else
            visit(*static_cast<CameraComponent *>(elem.get()));
    }
}


void MoveVisitor::visit(Composite &composite) const {
    for (auto &elem: composite) {
        if (elem->isComposite())
            visit(*static_cast<Composite *>(elem.get()));
        else if (elem->isVisible())
            visit(*static_cast<ModelComponent *>(elem.get()));
        else
            visit(*static_cast<CameraComponent *>(elem.get()));
    }
}


void MoveVisitor::visit(ModelComponent &component) const {
    MatrixTransformator transformator;
    transformator.move(_x, _y, _z);
    auto model = component.model;
    model->transform(transformator);
}


void MoveVisitor::visit(CameraComponent &component) const {
    auto camera = component.camera;
    camera->move(_x, _y, _z);
}


void RotateVisitor::visit(ModelComponent &component) const {
    MatrixTransformator transformator;
    transformator.rotate(_dir, _value);
    auto model = component.model;
    model->transform(transformator);
}


void RotateVisitor::visit(CameraComponent &component) const {
    auto camera = component.camera;
    camera->rotate(_value * (_dir == Direction::X),
                   _value * (_dir == Direction::Y),
                   _value * (_dir == Direction::Z));
}


void ScaleVisitor::visit(ModelComponent &component) const {
    MatrixTransformator transformator;
    transformator.scale(_value);
    auto model = component.model;
    model->transform(transformator);
}
