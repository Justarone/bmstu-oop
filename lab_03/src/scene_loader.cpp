#include "scene_loader.hpp"

MySceneBuilder::MySceneBuilder(ObjectLoader &cLoader, ObjectLoader &mLoader): 
    _cLoader(cLoader), _mLoader(mLoader) {};

void MySceneBuilder::buildComponent(std::ifstream &input) {
    size_t nCams, nModels;
    input >> nModels >> nCams;

    _isBuilt = true;
    _data.reset(new Composite());
    try {
        for (size_t i = 0; i < nModels; ++i)
            _data->add(_mLoader.getObject(input));
        for (size_t i = 0; i < nCams; ++i)
            _data->add(_cLoader.getObject(input));
    } catch(AppBaseException &) {
        _isBuilt = false;
    }
}

shared_ptr<Component> MySceneBuilder::getComponent() {
    return _data;
}

bool MySceneBuilder::isBuilt() {
    return _isBuilt;
}


SceneLoader::SceneLoader(shared_ptr<BaseSceneBuilder> builder, const char *filename):
                    _builder(builder), _filename(filename) {}


shared_ptr<Component> SceneLoader::getComponent() {
    std::ifstream input(_filename);
    if (input)
        _builder->buildComponent(input);
    input.close();

    shared_ptr<Component> component;
    if (_builder->isBuilt())
        component = _builder->getComponent();
    else
        throw AppInvalidArgument("Bad file: can't build model");
    return component;
}
