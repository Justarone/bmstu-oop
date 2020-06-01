#pragma once

#include "managers.hpp"
#include <vector>
#include "scene.hpp"

enum class ObjectType {
    MODEL,
    CAMERA,
    SCENE
};

// ADD == COPY
class AppFacade {
private:
    DrawManager _drawManager;
    LoadManager _loadManager;
    TransformMananger _transformManager;
    SceneManager _sceneManager;
    Scene _scene;
public:
    void loadScene(const char *filename);
    void addModel();
    void removeModel();
    void nextModel();
    void prevModel();
    void setModel(size_t index);
    void addCamera();
    void removeCamera();
    void nextCamera();
    void prevCamera();
    void setCamera(size_t index);
    void addScene();
    void removeScene();
    void setScene(size_t index);
    void nextScene();
    void prevScene();
    void drawScene();
    void transformModel(shared_ptr<BaseComponentVisitor> &visitor);
    void transformCamera(shared_ptr<BaseComponentVisitor> &visitor);
    void transformScene(shared_ptr<BaseComponentVisitor> &visitor);
};
