#pragma once

#include <vector>

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

class SceneManager: public BaseManager {
    size_t _curCam, _curModel, _curScene;
    void _addModel(/*args?*/) {};
    void _removeModel(/*args?*/) {};
    void _setModel(/*args?*/) {};
    void _addCamera(/*args?*/) {};
    void _removeCamera(/*args?*/) {};
    void _setCamera(/*args?*/) {};
    void _setScene() {};
    void _addScene() {};
    void _removeScene() {};
public:
    virtual void operation(BaseManagerCommand &) override {};
};

class DrawManager: public BaseManager {
    void _drawScene(/*args?*/);
public:
    virtual void operation(BaseManagerCommand &) override {};
};
