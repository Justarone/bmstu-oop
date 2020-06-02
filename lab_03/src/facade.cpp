#include "facade.hpp"

void AppFacade::loadScene(const char *filename) {
    std::cout << "loadScene method" << std::endl;
}

void AppFacade::transformModel(shared_ptr<BaseComponentVisitor> visitor) {
    std::cout << "transformModel method" << std::endl;
}

void AppFacade::transformCamera(shared_ptr<BaseComponentVisitor> visitor) {
    std::cout << "transformCamera method" << std::endl;
}

void AppFacade::transformScene(shared_ptr<BaseComponentVisitor> visitor) {
    std::cout << "transformScene method" << std::endl;
}

void AppFacade::addModel() {
    std::cout << "addModel method" << std::endl;
}

void AppFacade::addCamera() {
    std::cout << "addCamera method" << std::endl;
}

void AppFacade::addScene() {
    std::cout << "addScene method" << std::endl;
}

void AppFacade::removeModel() {
    std::cout << "removeModel method" << std::endl;
}

void AppFacade::removeCamera() {
    std::cout << "removeCamera method" << std::endl;
}

void AppFacade::removeScene() {
    std::cout << "removeScene method" << std::endl;
}

void AppFacade::changeModel(size_t diff) {
    std::cout << "changeModel method" << std::endl;
}

void AppFacade::changeCamera(size_t diff) {
    std::cout << "changeCamera method" << std::endl;
}

void AppFacade::changeScene(size_t diff) {
    std::cout << "changeScene method" << std::endl;
}

void AppFacade::drawScene(shared_ptr<BaseDrawingFactory> factory, shared_ptr<BaseProector> proector) {
    std::cout << "drawScene method" << std::endl;
}
