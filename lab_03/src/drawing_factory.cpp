#include "drawing_factory.hpp"

GtkDrawingFactory::GtkDrawingFactory(const Cairo::RefPtr<Cairo::Context> &cr): _cr(cr), _drawer(nullptr) {}

shared_ptr<BaseDrawer> GtkDrawingFactory::createDrawer() {
    if (_drawer)
        return _drawer;
    _drawer.reset(new GtkDrawer(_cr));
    return _drawer;
}
