#pragma once

#include <iostream>
#include "components.hpp"
#include "object_type.hpp"

//using ComponentIterator = VecIterator<shared_ptr<Component>>;
//using ComponentIterator = std::vector<shared_ptr<Component>>::const_iterator;

// Использовать итераторы
class Scene {
    vector<shared_ptr<Component>> _data;
    int _curScene = -1;

    bool _checkScene(int index);
    void _removeBadScenes();
    int _countObjects(ObjectType ot);
public:
    ComponentIterator getIterator(int index, ObjectType ot);
    void addComponent(shared_ptr<Component>, ObjectType ot);
    void removeComponent(ComponentIterator it, ObjectType ot);
    shared_ptr<Component> getComponent(int index, ObjectType ot);
    int setScene(int index);
    int updateState(int index, ObjectType ot);
};
