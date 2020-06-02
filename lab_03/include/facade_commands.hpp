#pragma once

#include "facade.hpp"

class BaseFacadeCommand {
public:
    virtual void execute(AppFacade &facade) = 0;
};


class LoadFacadeCommand: public BaseFacadeCommand {
    const char *_filename;
public:
    explicit LoadFacadeCommand(const char *filename): _filename(filename) {}
    virtual void execute(AppFacade &facade) override;
};


class TransformFacadeCommand: public BaseFacadeCommand {
    shared_ptr<BaseComponentVisitor> _visitor;
    ObjectType _ot;
public:
    explicit TransformFacadeCommand(shared_ptr<BaseComponentVisitor> visitor, ObjectType ot): 
    _visitor(visitor), _ot(ot) {}
    virtual void execute(AppFacade &facade) override;
};


class DrawFacadeCommand: public BaseFacadeCommand {
    shared_ptr<BaseDrawingFactory> _factory;
public:
    explicit DrawFacadeCommand(shared_ptr<BaseDrawingFactory> factory): _factory(factory) {}
    virtual void execute(AppFacade &facade) override;
};


class AddFacadeCommand: public BaseFacadeCommand {
    ObjectType _ot;
public:
    explicit AddFacadeCommand(ObjectType ot): _ot(ot) {}
    virtual void execute(AppFacade &facade) override;
};


class RemoveFacadeCommand: public BaseFacadeCommand {
    ObjectType _ot;
public:
    explicit RemoveFacadeCommand(ObjectType ot): _ot(ot) {}
    virtual void execute(AppFacade &facade) override;
};


class ChangeFacadeCommand: public BaseFacadeCommand {
    ObjectType _ot;
    size_t _diff; // next = 1, prev = -1;
public:
    explicit ChangeFacadeCommand(ObjectType ot, size_t diff): _ot(ot), _diff(diff) {}
    virtual void execute(AppFacade &facade) override;
};


void LoadFacadeCommand::execute(AppFacade &facade) {}
void TransformFacadeCommand::execute(AppFacade &facade) {}
void DrawFacadeCommand::execute(AppFacade &facade) {}
void AddFacadeCommand::execute(AppFacade &facade) {}
void RemoveFacadeCommand::execute(AppFacade &facade) {}
void ChangeFacadeCommand::execute(AppFacade &facade) {}
