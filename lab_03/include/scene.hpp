#pragma once

#include <iostream>
#include "components.hpp"
#include "object_type.hpp"

using ComponentIterator = std::vector<shared_ptr<Component>>::const_iterator;

class Scene {
    vector<shared_ptr<Component>> _data;
    int _curScene = -1;
    ComponentIterator _getIterator(int index, ObjectType ot);
public:
    void addComponent(shared_ptr<Component> &, ObjectType ot);
    void removeComponent(int index, ObjectType ot);
    shared_ptr<Component> getComponent(int index, ObjectType ot);
    int setScene(int index);
};
