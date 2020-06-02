#pragma once

#include "facade.hpp"
#include "drawing_factory.hpp"
#include "proector.hpp"

class BaseFacadeCommand {
public:
    virtual void execute(AppFacade &facade) = 0;
};


class LoadFacadeCommand: public BaseFacadeCommand {
    const char *_filename;
public:
    explicit LoadFacadeCommand(const char *filename);
    virtual void execute(AppFacade &facade) override;
};


class TransformFacadeCommand: public BaseFacadeCommand {
    shared_ptr<BaseComponentVisitor> _visitor;
    ObjectType _ot;
public:
    explicit TransformFacadeCommand(shared_ptr<BaseComponentVisitor> visitor, ObjectType ot);
    virtual void execute(AppFacade &facade) override;
};


class DrawFacadeCommand: public BaseFacadeCommand {
    shared_ptr<BaseDrawingFactory> _factory;
    shared_ptr<BaseProector> _proector;
public:
    explicit DrawFacadeCommand(shared_ptr<BaseDrawingFactory> factory, shared_ptr<BaseProector> proector);
    virtual void execute(AppFacade &facade) override;
};


class AddFacadeCommand: public BaseFacadeCommand {
    ObjectType _ot;
public:
    explicit AddFacadeCommand(ObjectType ot);
    virtual void execute(AppFacade &facade) override;
};


class RemoveFacadeCommand: public BaseFacadeCommand {
    ObjectType _ot;
public:
    explicit RemoveFacadeCommand(ObjectType ot);
    virtual void execute(AppFacade &facade) override;
};


class ChangeFacadeCommand: public BaseFacadeCommand {
    ObjectType _ot;
    size_t _diff; // next = 1, prev = -1;
public:
    explicit ChangeFacadeCommand(ObjectType ot, size_t diff);
    virtual void execute(AppFacade &facade) override;
};
