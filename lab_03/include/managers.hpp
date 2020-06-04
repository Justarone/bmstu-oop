#pragma once

#include <vector>

#include "proector.hpp"
#include "object_type.hpp"
#include "scene.hpp"
#include "scene_loader.hpp"
#include "drawer.hpp"
#include "components.hpp"

template <typename T>
using vector = std::vector<T>;

class BaseManager {};

class LoadManager: public BaseManager {
public:
    shared_ptr<Component> uploadScene(const char *filename);
};


class TransformMananger: public BaseManager {
public:
    void transformComponent(shared_ptr<Component> component,
        shared_ptr<BaseComponentVisitor> visitor);
};


class DrawManager: public BaseManager {
public:
    void drawScene(shared_ptr<Component> component, shared_ptr<BaseCamera> cam,
        shared_ptr<BaseDrawer> drawer, shared_ptr<BaseProector> proector);
};


class SceneManager: public BaseManager {
    Scene _scene;
    size_t _curCam, _curModel, _curScene;
    bool _stateCheck();
public:
    void addComponent(ObjectType ot);
    void addComponent(shared_ptr<Component> component, ObjectType ot);
    void removeComponent(ObjectType ot);
    void changeComponent(int diff, ObjectType ot);
    shared_ptr<Component> getComponent(ObjectType ot);
};
