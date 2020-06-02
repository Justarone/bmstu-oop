#pragma once

#include "drawer.hpp"

class BaseDrawingFactory {
public:
    virtual shared_ptr<BaseDrawer> createDrawer() = 0;
};


class GtkDrawingFactory: public BaseDrawingFactory {
    Gtk::DrawingArea &_da;
    shared_ptr<BaseDrawer> _drawer;
public:
    explicit GtkDrawingFactory(Gtk::DrawingArea &da): _da(da), _drawer(nullptr) {}
    virtual shared_ptr<BaseDrawer> createDrawer() override;
};

shared_ptr<BaseDrawer> GtkDrawingFactory::createDrawer() {
    if (_drawer)
        return _drawer;
    _drawer.reset(new GtkDrawer(_da));
    return _drawer;
}
