#pragma once

#include "components.hpp"
#include "model.hpp"

#include <iostream>
#include <fstream>

class BaseObjectBuilder {
protected:
    bool _isBuilt = false;
public:
    virtual bool isBuilt();
    virtual void buildObject() = 0;
    virtual void buildData(std::ifstream &input) = 0;
    virtual shared_ptr<Component> getObject() = 0;
};

class MyCameraBuilder: public BaseObjectBuilder {
    shared_ptr<BaseCamera> _camera = nullptr;
public:
    virtual void buildObject() override;
    virtual void buildData(std::ifstream &input) override;
    virtual shared_ptr<Component> getObject() override;
};

class MyModelBuilder: public BaseObjectBuilder {
    shared_ptr<BaseModel> _model = nullptr;
    vector<Point> _points;
    vector<Link> _links;
    vector<Point> _buildPoints(std::ifstream &input);
    vector<Link> _buildLinks(std::ifstream &input);
public:
    virtual void buildObject() override;
    virtual void buildData(std::ifstream &input) override;
    virtual shared_ptr<Component> getObject() override;
};

class ObjectLoader {
    shared_ptr<BaseObjectBuilder> _builder;
public:
    ObjectLoader(shared_ptr<BaseObjectBuilder> builder);
    shared_ptr<Component> getObject(std::ifstream &input);
};
