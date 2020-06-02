#pragma once

#include <iostream>

#include "managers.hpp"
#include "visitor.hpp"
#include <vector>
#include "scene.hpp"
#include "proector.hpp"
#include "drawing_factory.hpp"

enum class ObjectType {
    MODEL,
    CAMERA,
    SCENE
};

// ADD == COPY
class AppFacade {
private:
    Scene _scene;
    DrawManager _drawManager;
    LoadManager _loadManager;
    TransformMananger _transformManager;
    SceneManager _sceneManager;
public:
    void loadScene(const char *filename);
    void transformModel(shared_ptr<BaseComponentVisitor> visitor);
    void transformCamera(shared_ptr<BaseComponentVisitor> visitor);
    void transformScene(shared_ptr<BaseComponentVisitor> visitor);
    void addModel();
    void addCamera();
    void addScene();
    void removeModel();
    void removeCamera();
    void removeScene();
    void changeModel(size_t diff);
    void changeCamera(size_t diff);
    void changeScene(size_t diff);
    void drawScene(shared_ptr<BaseDrawingFactory> factory, shared_ptr<BaseProector> proector);
};
