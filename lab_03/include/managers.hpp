#pragma once

#include <vector>

#include "scene.hpp"
#include "managers_commands.hpp"
#include "components.hpp"

template <typename T>
using vector = std::vector<T>;

class BaseManager {
public:
    virtual void operation(BaseManagerCommand &) = 0;
};

class LoadManager: public BaseManager {
    vector<shared_ptr<Component>> _uploadScene(const char *filename) {
        return {};
    }
public:
    virtual void operation(BaseManagerCommand &) override {};
};

class TransformMananger: public BaseManager {
    void _move(/*args?*/) {};
    void _scale(/*args?*/) {};
    void _rotate(/*args?*/) {};
public:
    virtual void operation(BaseManagerCommand &) override {};
};


class DrawManager: public BaseManager {
    void _drawScene(Scene &scene, shared_ptr<BaseDrawer> drawer, shared_ptr<BaseProector> proector);
public:
    virtual void operation(BaseManagerCommand &) override {};
};
