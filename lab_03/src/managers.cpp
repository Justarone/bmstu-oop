#include "managers.hpp"


shared_ptr<Component> LoadManager::uploadScene(const char *filename) {
    shared_ptr<BaseObjectBuilder> modelBuilder(new MyModelBuilder());
    shared_ptr<BaseObjectBuilder> cameraBuilder(new MyCameraBuilder());
    ObjectLoader cameraLoader(cameraBuilder);
    ObjectLoader modelLoader(modelBuilder);
    shared_ptr<BaseSceneBuilder> sceneBuilder(new MySceneBuilder(cameraLoader, modelLoader));
    SceneLoader loader(sceneBuilder, filename);
    return loader.getComponent();
}

void TransformMananger::transformComponent(shared_ptr<Component> component,
        shared_ptr<BaseComponentVisitor> visitor) {
    component->accept(*visitor);
}

void DrawManager::drawScene(shared_ptr<Component> component, shared_ptr<BaseCamera> cam,
        shared_ptr<BaseDrawer> drawer, shared_ptr<BaseProector> proector) {
    shared_ptr<BaseComponentVisitor> drawVisitor(new DrawVisitor(drawer, cam, proector));
    component->accept(*drawVisitor);
}

void SceneManager::addComponent(shared_ptr<Component> component, ObjectType ot) {
    _scene.addComponent(component, ot);
}

void SceneManager::addComponent(ObjectType ot) {
    if (!_stateCheck())
        throw AppInvalidArgument("Bad state of scene");
    auto component = getComponent(ot);
    addComponent(component->clone(), ot);
}

void SceneManager::removeComponent(ObjectType ot) {
    if (!_stateCheck())
        throw AppInvalidArgument("Bad state of scene");
    int index = ot == ObjectType::SCENE ? _curScene : (ot == ObjectType::MODEL ? _curModel : _curCam);
    _scene.removeComponent(index, ot);
}

void SceneManager::changeComponent(int diff, ObjectType ot) {
    if (!_stateCheck())
        throw AppInvalidArgument("Bad state of scene");

    if (ot == ObjectType::SCENE)
        _curScene += diff, _curCam = 0, _curModel = 0;
    else if (ot == ObjectType::MODEL)
        _curModel += diff;
    else if (ot == ObjectType::CAMERA)
        _curCam += diff;
    else
        throw AppInvalidArgument("Bad object type");
}

shared_ptr<Component> SceneManager::getComponent(ObjectType ot) {
    if (!_stateCheck())
        throw AppInvalidArgument("Bad state of scene");
    shared_ptr<Component> res;
    res = ot == ObjectType::SCENE ? _scene.getComponent(_curScene, ot) : 
        (ot == ObjectType::MODEL ? _scene.getComponent(_curModel, ot) : _scene.getComponent(_curCam, ot));
    return res;
}

bool SceneManager::_stateCheck() {
    try {
        if (_curScene < 0)
            _curScene = 0;
        _curScene = _scene.updateState(_curScene, ObjectType::SCENE);
        _curModel = _scene.updateState(_curModel, ObjectType::MODEL);
        _curCam = _scene.updateState(_curCam, ObjectType::CAMERA);
    } catch (AppBaseException &err) {
        return false;
    }
    return true;
}
