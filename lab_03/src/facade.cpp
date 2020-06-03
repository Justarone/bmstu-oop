#include "facade.hpp"

void AppFacade::loadScene(const char *filename) {
    std::cout << "loadScene method" << std::endl;
}

void AppFacade::transformComponent(shared_ptr<BaseComponentVisitor> visitor, ObjectType ot) {
    std::cout << "transformComponent method" << std::endl;
}

void AppFacade::addComponent(ObjectType ot) {
    std::cout << "addComponent method" << std::endl;
}

void AppFacade::removeComponent(ObjectType ot) {
    std::cout << "removeComponent method" << std::endl;
}

void AppFacade::changeComponent(size_t diff, ObjectType ot) {
    std::cout << "changeComponent method" << std::endl;
}

void AppFacade::drawScene(shared_ptr<BaseDrawingFactory> factory, shared_ptr<BaseProector> proector) {
    std::cout << "drawScene method" << std::endl;
}

