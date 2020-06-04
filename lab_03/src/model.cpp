#include "model.hpp"

vector<Link> &FrameModel::getLinks() {
    return _links;
}

vector<Point> &FrameModel::getPoints() {
    return _points;
}

void FrameModel::transform(BaseTransformator &transformator) {
    auto &points = getPoints();
    for (auto &point: points) {
        std::cout << "POINT BEFORE: ";
        std::cout << point.getX() << "//" << point.getY() << "//" << point.getZ() << std::endl;
        point = transformator.transform(point);
        std::cout << "POINT AFTER: ";
        std::cout << point.getX() << "//" << point.getY() << "//" << point.getZ() << std::endl;
    }
}
