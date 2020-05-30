#include <components.hpp>

bool Composite::add(shared_ptr<Component> &element) {
    try {
        _data.push_back(element); 
    } catch (std::exception &err) {
        return false;
    }
    return true;
}

bool Composite::remove(ComponentIterator &it) {
    try {
        _data.erase(it);
    } catch (std::exception &err) {
        return false;
    }
    return true;
}
