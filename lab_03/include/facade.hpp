#pragma once

#include <iostream>

#include "managers.hpp"
#include "visitor.hpp"
#include "scene.hpp"
#include "proector.hpp"
#include "object_type.hpp"
#include "drawing_factory.hpp"
#include "scene_loader.hpp"

// ADD == COPY
class AppFacade {
private:
    DrawManager _drawManager;
    LoadManager _loadManager;
    TransformMananger _transformManager;
    SceneManager _sceneManager;
public:
    void loadScene(const char *filename);
    void transformComponent(shared_ptr<BaseComponentVisitor> visitor, ObjectType ot);
    void addComponent(ObjectType ot);
    void removeComponent(ObjectType ot);
    void changeComponent(int diff, ObjectType ot);
    void drawScene(shared_ptr<BaseDrawingFactory> factory, shared_ptr<BaseProector> proector);
};
