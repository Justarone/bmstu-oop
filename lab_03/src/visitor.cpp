#include "visitor.hpp"


RotateVisitor::RotateVisitor(Direction dir, double value): _dir(dir), _value(value) {}

DrawVisitor::DrawVisitor(shared_ptr<BaseDrawer> drawer, shared_ptr<BaseCamera> cam,
        shared_ptr<BaseProector> proector): _drawer(drawer), _cam(cam), _proector(proector) {}

MoveVisitor::MoveVisitor(double x, double y, double z): _x(x), _y(y), _z(z) {}

ScaleVisitor::ScaleVisitor(double value): _value(value) {}

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
    shared_ptr<BaseTransformStrategy> strat(new MoveStrategy(_x, _y, _z));
    MyTransformator transformator(strat);
    shared_ptr<BaseModel> model = component.model;
    model->transform(transformator);
}


void MoveVisitor::visit(CameraComponent &component) const {
    shared_ptr<BaseCamera> camera = component.camera;
    camera->move(_x, _y, _z);
}


void RotateVisitor::visit(ModelComponent &component) const {
    shared_ptr<BaseTransformStrategy> strat(new RotateStrategy(_dir, _value));
    MyTransformator transformator(strat);
    shared_ptr<BaseModel> model = component.model;
    model->transform(transformator);
}


void RotateVisitor::visit(CameraComponent &component) const {
    shared_ptr<BaseCamera> camera = component.camera;
    camera->rotate(_value * (_dir == Direction::X),
                   _value * (_dir == Direction::Y),
                   _value * (_dir == Direction::Z));
}


void ScaleVisitor::visit(ModelComponent &component) const {
    shared_ptr<BaseTransformStrategy> strat(new ScaleStrategy(_value));
    MyTransformator transformator(strat);
    shared_ptr<BaseModel> model = component.model;
    model->transform(transformator);
}


void DrawVisitor::visit(Composite &composite) const {
    for (auto &elem: composite) {
        if (elem->isComposite())
            visit(*static_cast<Composite *>(elem.get()));
        else if (elem->isVisible())
            visit(*static_cast<ModelComponent *>(elem.get()));
        else
            visit(*static_cast<CameraComponent *>(elem.get()));
    }
}

void DrawVisitor::visit(CameraComponent &) const {}

void DrawVisitor::visit(ModelComponent &model) const {
    shared_ptr<BaseModel> modelPtr = model.model; 
    FrameModel *model3d = dynamic_cast<FrameModel*>(modelPtr.get());
    const auto &links = model3d->getLinks();
    const auto &points = model3d->getPoints();
    for (size_t i = 0; i < links.size(); ++i) {
        Point2d p1 = _proector->getProection(points[links[i].getFirst()], _cam);
        Point2d p2 = _proector->getProection(points[links[i].getSecond()], _cam);
        _drawer->drawLine(p1, p2);
    }
}
