#pragma once

#include <vector>

#include "proector.hpp"
#include "object_type.hpp"
#include "scene.hpp"
#include "components.hpp"
#include "scene_loader.hpp"
#include "drawer.hpp"

template <typename T>
using vector = std::vector<T>;

class BaseManager {};

class LoadManager: public BaseManager {
public:
    vector<shared_ptr<Component>> uploadScene(const char *filename, SceneLoader &loader);
};

class TransformMananger: public BaseManager {
public:
    void transformComponent(shared_ptr<BaseComponentVisitor> visitor, ObjectType ot);
};


class DrawManager: public BaseManager {
public:
    void drawScene(Scene &scene, shared_ptr<BaseDrawer> drawer, shared_ptr<BaseProector> proector);
};

class SceneManager: public BaseManager {
    size_t _curCam, _curModel, _curScene;
public:
    void addComponent(ObjectType ot);
    void removeComponent(ObjectType ot);
    void changeComponent(size_t diff, ObjectType ot);
    void getComponent(ObjectType ot);
};
