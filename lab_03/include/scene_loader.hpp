#pragma once

#include "components.hpp"
#include <iostream>
#include <fstream>
#include "object_loader.hpp"

class BaseSceneBuilder {
public:
    virtual void buildComponent(std::ifstream &input) = 0;
    virtual shared_ptr<Component> getComponent() = 0;
    virtual bool isBuilt() = 0;
};

class MySceneBuilder: public BaseSceneBuilder {
    ObjectLoader &_cLoader;
    ObjectLoader &_mLoader;
    bool _isBuilt = false;
    shared_ptr<Component> _data = nullptr;
public:
    MySceneBuilder(ObjectLoader &_cLoader, ObjectLoader &_mLoader);
    virtual void buildComponent(std::ifstream &input) override;
    virtual shared_ptr<Component> getComponent() override;
    virtual bool isBuilt() override;
};


class SceneLoader {
    shared_ptr<BaseSceneBuilder> _builder;
    const char *_filename;
public:
    explicit SceneLoader(shared_ptr<BaseSceneBuilder> builder, const char *filename);
    shared_ptr<Component> getComponent();
};
