#include "scene.hpp"

void Scene::addComponent(shared_ptr<Component> component, ObjectType ot) {
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

bool Scene::_checkScene(int index) {
    bool hasCam = false, hasModel = false;
    auto curScene = _data[index];
    for (auto it = curScene->begin(); it < curScene->end() && !(hasCam && hasModel); it++) {
        if ((*it)->isVisible())
            hasModel = true;
        else if (!(*it)->isComposite())
            hasCam = true;
    }
    return hasCam && hasModel;
}

void Scene::_removeBadScenes() {
    for (int i = static_cast<int>(_data.size()) - 1; i >= 0; --i)
        if (!_checkScene(i))
            _data.erase(_data.begin() + i);
}

int Scene::_countObjects(ObjectType ot) {
    if (ot == ObjectType::SCENE)
        return static_cast<int>(_data.size()) - 1;

    else if (ot == ObjectType::MODEL || ot == ObjectType::CAMERA) {
        int cntModels = 0, cntCams = 0;

        std::cout << std::endl;
        auto scene = dynamic_cast<Composite&>(*_data[_curScene].get());
        for (auto elem: scene) {
            if (elem->isVisible())
                cntModels++;
            else if (!elem->isComposite())
                cntCams++;
        }
        std::cout << std::endl;

        std::cout << "cntModels: " << cntModels << " and cntCams: " << cntCams << std::endl;
        return ot == ObjectType::MODEL ? cntModels : cntCams;
    }

    throw AppInvalidArgument("Bad object type");
}

int Scene::updateState(int index, ObjectType ot) {
    _removeBadScenes();
    if (_data.size() == 0)
        throw AppBadState("No scenes");
    if (ot == ObjectType::SCENE) {
        _curScene = index < static_cast<int>(_data.size()) ? index : 0;
        return _curScene; // _data.size() - 1
    }
    
    else if (ot == ObjectType::MODEL || ot == ObjectType::CAMERA) {
        int cnt = _countObjects(ot);
        return index < cnt ? index : 0;
    }

    throw AppInvalidArgument("Invalid object type.");
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
