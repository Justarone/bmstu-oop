#include "object_loader.hpp"

bool BaseObjectBuilder::isBuilt() {
    return _isBuilt;
}

void MyCameraBuilder::buildObject() {
    _camera.reset(new Camera());
}

void MyCameraBuilder::buildData(std::ifstream &input) {
    double x, y, z;
    if (input >> x >> y >> z)
        _camera->setPos(x, y, z);
    else
        throw AppInvalidArgument("Can't read camera data");

    if (input >> x >> y >> z)
        _camera->setNormal(x, y, z);
    else
        throw AppInvalidArgument("Can't read camera data");

    _isBuilt = true;
}

shared_ptr<Component> MyCameraBuilder::getObject() {
    shared_ptr<Component> component(new CameraComponent(_camera));
    return component;
}

void MyModelBuilder::buildObject() {
    _model.reset(new FrameModel());
}

void MyModelBuilder::buildData(std::ifstream &input) {
    FrameModel &model = dynamic_cast<FrameModel &>(*_model);
    vector<Point> &pts = model.getPoints();
    vector<Link> &links = model.getLinks();
    pts = _buildPoints(input);
    links = _buildLinks(input);
}

vector<Point> MyModelBuilder::_buildPoints(std::ifstream &input) {
    size_t n = 0;
    if (!(input >> n))
        throw AppInvalidArgument("Can't read points amount");
    vector<Point> tmp;

    double x, y, z;
    for (size_t i = 0; i < n; ++i) {
        if (input >> x >> y >> z)
            tmp.push_back(Point(x, y, z));
        else 
            throw AppInvalidArgument("Bad data in file: can't build model's points");
    }

    return tmp;
}

vector<Link> MyModelBuilder::_buildLinks(std::ifstream &input) {
    size_t n = 0;
    if (!(input >> n))
        throw AppInvalidArgument("Can't read links amount");
    vector<Link> tmp;

    size_t l1, l2;
    for (size_t i = 0; i < n; ++i) {
        if (input >> l1 >> l2)
            tmp.push_back(Link(l1, l2));
        else
            throw AppInvalidArgument("Bad data in file: can't read link number");
    }
    return tmp;
}

shared_ptr<Component> MyModelBuilder::getObject() {
    return shared_ptr<Component>(new ModelComponent(_model));
}

ObjectLoader::ObjectLoader(shared_ptr<BaseObjectBuilder> builder): _builder(builder) {};

shared_ptr<Component> ObjectLoader::getObject(std::ifstream &input) {
    _builder->buildObject();
    _builder->buildData(input);
    if (_builder->isBuilt())
        return _builder->getObject();
    else
        throw AppInvalidArgument("Failed to build object");
}
