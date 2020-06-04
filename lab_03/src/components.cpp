#include "components.hpp"

Component::~Component() {}

bool Composite::add(shared_ptr<Component> element) {
    try {
        _data.push_back(element); 
    } catch (std::exception &err) {
        return false;
    }
    return true;
}

bool Composite::remove(ComponentIterator &it) {
    try {
        _data.erase(it);
    } catch (std::exception &err) {
        return false;
    }
    return true;
}

bool Component::isVisible() const {
    return false; 
}

bool Component::isComposite() const { 
    return false; 
}

bool Component::add(shared_ptr<Component>) {
    return false;
}

bool Component::remove(ComponentIterator &) {
    return false;
}

ComponentIterator Component::begin() {
    return ComponentIterator();
}

ComponentIterator Component::end() {
    return ComponentIterator();
}

Composite &Composite::operator=(vector<shared_ptr<Component>> data) {
    _data = data;
    return *this;
}

void Composite::accept(const BaseComponentVisitor &visitor) {
    visitor.visit(*this);
}

bool Composite::isComposite() const {
    return true;
}

ComponentIterator Composite::begin() {
    return _data.begin();
}

ComponentIterator Composite::end() {
    return _data.end();
}

Composite::Composite(vector<shared_ptr<Component>> data): _data(data) {};
ModelComponent::ModelComponent(shared_ptr<BaseModel> model): model(model) {};

bool ModelComponent::isVisible() const {
    return true; 
}

void ModelComponent::accept(const BaseComponentVisitor &visitor) {
    visitor.visit(*this);
}

CameraComponent::CameraComponent(shared_ptr<BaseCamera> cam): camera(cam) {};

void CameraComponent::accept(const BaseComponentVisitor &visitor) {
    visitor.visit(*this);
}

shared_ptr<Component> Composite::clone() {
    shared_ptr<Component> newComposite(new Composite());
    for (auto &elem: _data)
        newComposite->add(elem->clone());
    return newComposite;
}

shared_ptr<Component> ModelComponent::clone() {
    shared_ptr<Component> newComponent(new ModelComponent(model->clone()));
    return newComponent;
}

shared_ptr<Component> CameraComponent::clone() {
    shared_ptr<Component> newComponent(new CameraComponent(camera->clone()));
    return newComponent;
}
