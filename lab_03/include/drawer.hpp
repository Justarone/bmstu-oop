#pragma once

#include <gtkmm-3.0/gtkmm.h>

#include "components.hpp"
#include "point2d.hpp"

class BaseDrawer {
public:
    virtual void drawLine(const Point2d &p1, const Point2d &p2) = 0;
    virtual void clear() = 0;
};


class GtkDrawer: public BaseDrawer {
    Gtk::DrawingArea &_drawingArea;
public:
    explicit GtkDrawer(Gtk::DrawingArea &area);
    virtual void drawLine(const Point2d &p1, const Point2d &p2) override;
    virtual void clear() override;
};

