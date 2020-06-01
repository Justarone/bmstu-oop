#pragma once

#include <gtkmm-3.0/gtkmm.h>

class BaseDrawer {
public:
    virtual void draw(const Scene &scene) = 0;
};


class GtkDrawer {
    Gtk::DrawingArea _drawingArea;
public:
    virtual void draw(const Scene &scene) override;
};
