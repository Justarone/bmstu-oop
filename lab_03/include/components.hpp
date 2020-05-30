#pragma once
#include <memory>
#include <vector>

#include "model.hpp"
#include "camera.hpp"
#include "visitor.hpp"

template <typename Type>
using shared_ptr = std::shared_ptr<Type>;

template <typename Type>
using vector = std::vector<Type>;

class Component;

using ComponentIterator = std::vector<shared_ptr<Component>>::const_iterator;

class Component {
public:
    virtual void accept(const BaseComponentVisitor &) = 0;
    virtual bool isVisible() { return false; }
    virtual bool isComposite() { 
        return false; 
    }
    virtual bool add(shared_ptr<Component> &) {
        return false;
    }
    virtual bool remove(ComponentIterator &) {
        return false;
    }
    virtual ComponentIterator begin() {
        return ComponentIterator();
    }
    virtual ComponentIterator end() {
        return ComponentIterator();
    }
    virtual ~Component() = 0;
};


class Composite: public Component {
    vector<shared_ptr<Component>> _data;
public:
    Composite() = default;
    Composite(const Composite &elem) = default;
    Composite(vector<shared_ptr<Component>> &data): _data(data) {};

    Composite &operator=(const Composite &elem) = default;
    Composite &operator=(vector<shared_ptr<Component>> data) {
        _data = data;
        return *this;
    }
    virtual void accept(const BaseComponentVisitor &visitor) override {
        visitor.visit(*this);
    }
    virtual bool isComposite() override {
        return true;
    }
    virtual bool add(shared_ptr<Component> &element) override;
    virtual bool remove(ComponentIterator &it) override;

    virtual ComponentIterator begin() override {
        return _data.begin();
    }
    virtual ComponentIterator end() override {
        return _data.end();
    }
};


class ModelComponent: public Component {
public:
    shared_ptr<BaseModel> model; // чтобы был полиморфизм, нужен указатель
    ModelComponent() = delete;
    ModelComponent(const ModelComponent &elem) = default;
    ModelComponent(shared_ptr<BaseModel> &model): model(model) {};
    ModelComponent &operator=(const ModelComponent &elem) = default;
    virtual bool isVisible() override { return true; }
    virtual void accept(const BaseComponentVisitor &visitor) override {
        visitor.visit(*this);
    }
};

class CameraComponent: public Component {
public:
    shared_ptr<BaseCamera> camera; // аналогично модели
    CameraComponent() = delete;
    CameraComponent(const CameraComponent &elem) = default;
    CameraComponent(shared_ptr<BaseCamera> &cam): camera(cam) {};
    CameraComponent &operator=(const CameraComponent &elem) = default;

    virtual void accept(const BaseComponentVisitor &visitor) override {
        visitor.visit(*this);
    }
};
