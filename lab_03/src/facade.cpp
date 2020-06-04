#include "facade.hpp"

void AppFacade::loadScene(const char *filename) {
    auto resComposite = _loadManager.uploadScene(filename);
    _sceneManager.addComponent(resComposite, ObjectType::SCENE);
}

void AppFacade::transformComponent(shared_ptr<BaseComponentVisitor> visitor, ObjectType ot) {
    auto component = _sceneManager.getComponent(ot);
    _transformManager.transformComponent(component, visitor);
}

void AppFacade::addComponent(ObjectType ot) {
    std::cout << "addComponent method" << std::endl;
}

void AppFacade::removeComponent(ObjectType ot) {
    std::cout << "removeComponent method" << std::endl;
}

void AppFacade::changeComponent(int diff, ObjectType ot) {
    std::cout << "changeComponent method" << std::endl;
}

void AppFacade::drawScene(shared_ptr<BaseDrawingFactory> factory, shared_ptr<BaseProector> proector) {
    shared_ptr<Component> curScene;
    shared_ptr<Component> curCam;
    try {
        curScene = _sceneManager.getComponent(ObjectType::SCENE);
        curCam = _sceneManager.getComponent(ObjectType::CAMERA);
    } catch (AppBaseException &err) {
        std::cout << "Nothing to draw\n";
    }

    if (!curScene || !curCam)
        return;

    shared_ptr<BaseDrawer> drawer = factory->createDrawer();
    drawer->clear();
    auto camera = dynamic_cast<CameraComponent *>(curCam.get())->camera;
    _drawManager.drawScene(curScene, camera, drawer, proector);
}
