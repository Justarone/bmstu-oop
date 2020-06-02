#include "facade_commands.hpp"

ChangeFacadeCommand::ChangeFacadeCommand(ObjectType ot, size_t diff): _ot(ot), _diff(diff) {}
RemoveFacadeCommand::RemoveFacadeCommand(ObjectType ot): _ot(ot) {}
AddFacadeCommand::AddFacadeCommand(ObjectType ot): _ot(ot) {}
LoadFacadeCommand::LoadFacadeCommand(const char *filename): _filename(filename) {}
TransformFacadeCommand::TransformFacadeCommand(shared_ptr<BaseComponentVisitor> visitor, ObjectType ot):
    _visitor(visitor), _ot(ot) {}
DrawFacadeCommand::DrawFacadeCommand(shared_ptr<BaseDrawingFactory> factory, shared_ptr<BaseProector> proector):
    _factory(factory), _proector(proector) {}


void LoadFacadeCommand::execute(AppFacade &facade) {
    facade.loadScene(_filename);
}

void TransformFacadeCommand::execute(AppFacade &facade) {
    switch(_ot) {
        case ObjectType::MODEL:
            facade.transformModel(_visitor);
            break;
        case ObjectType::SCENE:
            facade.transformScene(_visitor);
            break;
        case ObjectType::CAMERA:
            facade.transformCamera(_visitor);
            break;
        default:
            throw AppInvalidArgument("Incorrect object type");
    }
}

void DrawFacadeCommand::execute(AppFacade &facade) {
    facade.drawScene(_factory, _proector);
}

void AddFacadeCommand::execute(AppFacade &facade) {
    switch(_ot) {
        case ObjectType::MODEL:
            facade.addModel();
            break;
        case ObjectType::SCENE:
            facade.addScene();
            break;
        case ObjectType::CAMERA:
            facade.addCamera();
            break;
        default:
            throw AppInvalidArgument("Incorrect object type");
    }
}
void RemoveFacadeCommand::execute(AppFacade &facade) {
    switch(_ot) {
        case ObjectType::MODEL:
            facade.removeModel();
            break;
        case ObjectType::SCENE:
            facade.removeScene();
            break;
        case ObjectType::CAMERA:
            facade.removeCamera();
            break;
        default:
            throw AppInvalidArgument("Incorrect object type");
    }
}

void ChangeFacadeCommand::execute(AppFacade &facade) {
    switch(_ot) {
        case ObjectType::MODEL:
            facade.changeModel(_diff);
            break;
        case ObjectType::SCENE:
            facade.changeScene(_diff);
            break;
        case ObjectType::CAMERA:
            facade.changeCamera(_diff);
            break;
        default:
            throw AppInvalidArgument("Incorrect object type");
    }
}
