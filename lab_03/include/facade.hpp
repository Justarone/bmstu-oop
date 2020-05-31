#pragma once

#include "managers.hpp"

class AppFacade {
private:
    DrawManager _drawManager;
    LoadManager _loadManager;
    TransformMananger _transformManager;
    SceneManager _sceneManager;
    //Scene _scene;
public:
    void loadScene(const char *filename);
    void addModel(/*args?*/);
    void removeModel(/*args?*/);
    void addCamera(/*args?*/);
    void removeCamera(/*args?*/);
    void setCamera(/*args?*/);
    void addScene(/*args?*/);
    void removeScene(/*args?*/);
    void setScene(/*args?*/);
    void drawScene(/*args?*/);
    void transformModel(/*args?*/);
    void transformCamera(/*args?*/);
}
