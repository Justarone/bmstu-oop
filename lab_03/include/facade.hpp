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
    Scene _scene;
public:
    DrawManager drawManager;
    LoadManager loadManager;
    TransformMananger transformManager;
    SceneManager sceneManager;
};
