#include "drawing_factory.hpp"

GtkDrawingFactory::GtkDrawingFactory(Gtk::DrawingArea &da): _da(da), _drawer(nullptr) {}

shared_ptr<BaseDrawer> GtkDrawingFactory::createDrawer() {
    if (_drawer)
        return _drawer;
    _drawer.reset(new GtkDrawer(_da));
    return _drawer;
}
