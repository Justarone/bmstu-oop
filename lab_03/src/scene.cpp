#include "scene.hpp"

void Scene::addComponent(shared_ptr<Component> &component, ObjectType ot) {
    if (ot == ObjectType::SCENE && component->isComposite())
        _data.push_back(component);
    else if (!component->isComposite())
        _data[_curScene]->add(component);
    else
        throw AppInvalidArgument("Invalid elem to add");
}

void Scene::removeComponent(int index, ObjectType ot) {
    ComponentIterator it = _getIterator(index, ot);
    if (ot == ObjectType::SCENE)
        _data.erase(it);
    else
        _data[_curScene]->remove(it);
}

ComponentIterator Scene::_getIterator(int index, ObjectType ot) {
    if (_curScene < 0 || _curScene >= static_cast<int>(_data.size()))
        throw AppOutOfRange("Incorrect value of curScene index");
    if (ot == ObjectType::SCENE)
        return _data.begin() + _curScene;

    Composite &composite = dynamic_cast<Composite &>(*_data[_curScene]);

    if (ot == ObjectType::MODEL) {
        int i = -1;
        auto it = composite.begin();
        while (it < composite.end() && i != index) {
            if ((*it)->isVisible())
                ++i;
            if (index == i)
                return it;
            ++it;
        }
        throw AppOutOfRange("can't find model with that index");
    }

    else if(ot == ObjectType::CAMERA) {
        int i = -1;
        auto it = composite.begin();
        while (it < composite.end() && i != index) {
            if (!(*it)->isVisible())
                ++i;
            if (index == i)
                return it;
            ++it;
        }
        throw AppOutOfRange("can't find camera with that index");
    }

    throw AppInvalidArgument("Can't find requested elem");
}

shared_ptr<Component> Scene::getComponent(int index, ObjectType ot) {
    ComponentIterator it = _getIterator(index, ot);
    return *it;
}

int Scene::setScene(int index) {
    _curScene = index < static_cast<int>(_data.size()) ? index : 0;
    return _curScene;
}
