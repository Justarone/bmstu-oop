#pragma once

#include "object_type.hpp"
#include "drawing_factory.hpp"
#include "proector.hpp"
#include "managers.hpp"
#include "visitor.hpp"

template <typename T>
using vector = std::vector<T>;

class BaseManagerCommand {
public:
    virtual void execute(BaseManager &);
};

class DrawManagerCommand: public BaseManagerCommand {
    shared_ptr<BaseDrawingFactory> _factory;
    shared_ptr<BaseProector> _proector;
public: 
    DrawManagerCommand(shared_ptr<BaseDrawingFactory> factory, shared_ptr<BaseProector> proector);
    virtual void execute(BaseManager &) override;
};

class LoadManagerCommand: public BaseManagerCommand {
    const char *_filename;
    vector<shared_ptr<Component>> &_data;
public: 
    LoadManagerCommand(const char *filename, vector<shared_ptr<Component>> &data);
    void execute(BaseManager &) override;
};

class TransformManagerCommand: public BaseManagerCommand {
    ObjectType _ot;
    shared_ptr<BaseComponentVisitor> _visitor;
public: 
    TransformManagerCommand(shared_ptr<BaseComponentVisitor> visitor, ObjectType ot);
    void execute(BaseManager &) override;
};


DrawManagerCommand::DrawManagerCommand(shared_ptr<BaseDrawingFactory> factory,
        shared_ptr<BaseProector> proector): _factory(factory), _proector(proector) {}

void DrawManagerCommand::execute(BaseManager &inManager) {
    DrawManager &drawManager = dynamic_cast<DrawManager &>(inManager);
} // ????????????????????????????????//


LoadManagerCommand::LoadManagerCommand(const char *filename, vector<shared_ptr<Component>> &data):
                                                    _filename(filename), _data(data) {}


TransformManagerCommand::TransformManagerCommand(shared_ptr<BaseComponentVisitor> visitor, ObjectType ot):
    _visitor(visitor), _ot(ot) {};
