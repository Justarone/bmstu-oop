#include "managers.hpp"


vector<shared_ptr<Component>> LoadManager::uploadScene(const char *filename, SceneLoader &loader) {
    std::cout << "uploadScene manager method\n";
    return {};
}

void TransformMananger::transformComponent(shared_ptr<BaseComponentVisitor> visitor, ObjectType ot) {
    std::cout << "transformComponent transform manager method\n";
}

void DrawManager::drawScene(Scene &scene, shared_ptr<BaseDrawer> drawer, shared_ptr<BaseProector> proector) {
    std::cout << "drawScene draw manager method\n";
}

void SceneManager::addComponent(ObjectType ot) {
    std::cout << "addComponent method of Scene manager\n";
}

void SceneManager::removeComponent(ObjectType ot) {
    std::cout << "removeComponent method of scene manager\n"; 
}

void SceneManager::changeComponent(size_t diff, ObjectType ot) {
    std::cout << "changeComponent method of scene manager\n";
}

void SceneManager::getComponent(ObjectType ot) {
    std::cout << "getComponent method of scene manager\n";
}
