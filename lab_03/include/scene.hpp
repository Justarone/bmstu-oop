#pragma once

#include "components.hpp"

class Scene {
    vector<shared_ptr<Component>> _data;
public:
    void addModel(shared_ptr<Component> &);
    void removeModel(size_t index);
    void removeModel(ComponentIterator &);
    void getModel(size_t index);
    void addCamera(shared_ptr<Component> &);
    void removeCamera(size_t index);
    void removeCamera(ComponentIterator &);
    void getCamera(size_t index);
    void addScene(shared_ptr<Component> &);
    void removeScene(size_t index);
    void removeScene(ComponentIterator &);
    void getScene(size_t index);
    const vector<shared_ptr<Component>> &getData();
};
