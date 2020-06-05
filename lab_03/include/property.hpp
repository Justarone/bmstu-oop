#pragma once

#include <memory.h>

template <typename T>
using shared_ptr = std::shared_ptr<T>;

template <typename Owner, typename DataType>
class Property {
private:
    using Getter = shared_ptr<DataType> (Owner::*)() const;
    using Setter = void (Owner::*)(const shared_ptr<DataType>);

    Owner* _owner;
    Getter _methodGet;
    Setter _methodSet;

public:
    Property() = default;
    Property(Owner* owr, Getter getmethod, Setter setmethod):
        _owner(owr), _methodGet(getmethod), _methodSet(setmethod) {}

    void init(Owner* owr, Getter getmethod, Setter setmethod)
    {
        _owner.reset(owr);
        _methodGet = getmethod;
        _methodSet = setmethod;
    }

    operator shared_ptr<DataType>() { return (_owner->*_methodGet)(); }                          // Getter
    void operator=(const shared_ptr<DataType> data) { (_owner->*_methodSet)(data); } // Setter

    // Property(const Property&) = delete;
    // Property& operator=(const Property&) = delete;
};

