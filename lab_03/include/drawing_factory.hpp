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
    explicit GtkDrawingFactory(Gtk::DrawingArea &da);
    virtual shared_ptr<BaseDrawer> createDrawer() override;
};
