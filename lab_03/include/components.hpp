#pragma once
#include <memory>
#include "vector.hpp"
//#include <vector>

#include "model.hpp"
#include "camera.hpp"
#include "visitor.hpp"

class BaseComponentVisitor;

template <typename Type>
using shared_ptr = std::shared_ptr<Type>;

template <typename Type>
using vector = Vector<Type>;
//using vector = std::vector<Type>;

class Component;

using ComponentIterator = VecIterator<shared_ptr<Component>>;
//using ComponentIterator = std::vector<shared_ptr<Component>>::const_iterator;

class Component {
public:
    virtual void accept(const BaseComponentVisitor &) = 0;
    virtual bool isVisible() const;
    virtual bool isComposite() const;
    virtual shared_ptr<Component> clone() = 0;
    virtual bool add(shared_ptr<Component>);
    virtual bool remove(ComponentIterator &);
    virtual ComponentIterator begin();
    virtual ComponentIterator end();
    virtual ~Component() = 0;
};


class Composite: public Component {
    vector<shared_ptr<Component>> _data;
public:
    Composite() = default;
    Composite(const Composite &elem) = default;
    Composite(vector<shared_ptr<Component>> data);
    Composite &operator=(const Composite &elem) = default;
    Composite &operator=(vector<shared_ptr<Component>> data);
    virtual void accept(const BaseComponentVisitor &visitor) override;
    virtual bool isComposite() const override;
    virtual shared_ptr<Component> clone() override;
    virtual bool add(shared_ptr<Component> element) override;
    virtual bool remove(ComponentIterator &it) override;
    virtual ComponentIterator begin() override;
    virtual ComponentIterator end() override;
};


class ModelComponent: public Component {
public:
    // скрыть
    shared_ptr<BaseModel> model; // чтобы был полиморфизм, нужен указатель
    ModelComponent() = delete;
    ModelComponent(const ModelComponent &elem) = default;
    ModelComponent(shared_ptr<BaseModel> model);
    ModelComponent &operator=(const ModelComponent &elem) = default;
    virtual bool isVisible() const override;
    virtual void accept(const BaseComponentVisitor &visitor) override;
    virtual shared_ptr<Component> clone() override;
};

class CameraComponent: public Component {
public:
    // скрыть
    shared_ptr<BaseCamera> camera; // аналогично модели
    CameraComponent() = delete;
    CameraComponent(const CameraComponent &elem) = default;
    CameraComponent(shared_ptr<BaseCamera> cam);
    CameraComponent &operator=(const CameraComponent &elem) = default;
    virtual void accept(const BaseComponentVisitor &visitor) override;
    virtual shared_ptr<Component> clone() override;
};
