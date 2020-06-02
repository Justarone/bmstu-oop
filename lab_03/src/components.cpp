#include "components.hpp"

Component::~Component() {}

bool Composite::add(shared_ptr<Component> &element) {
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

bool Component::isVisible() {
    return false; 
}

bool Component::isComposite() { 
    return false; 
}

bool Component::add(shared_ptr<Component> &) {
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

bool Composite::isComposite() {
    return true;
}

ComponentIterator Composite::begin() {
    return _data.begin();
}

ComponentIterator Composite::end() {
    return _data.end();
}

Composite::Composite(vector<shared_ptr<Component>> &data): _data(data) {};
ModelComponent::ModelComponent(shared_ptr<BaseModel> &model): model(model) {};

bool ModelComponent::isVisible() { 
    return true; 
}

void ModelComponent::accept(const BaseComponentVisitor &visitor) {
    visitor.visit(*this);
}

CameraComponent::CameraComponent(shared_ptr<BaseCamera> &cam): camera(cam) {};

void CameraComponent::accept(const BaseComponentVisitor &visitor) {
    visitor.visit(*this);
}
