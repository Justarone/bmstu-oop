#pragma once

#include <gtkmm-3.0/gtkmm.h>

#include "components.hpp"
#include "point2d.hpp"

class BaseDrawer {
public:
    virtual void draw(const shared_ptr<Component> scene, shared_ptr<BaseCamera> camera) = 0;
    virtual void clear() = 0;
};


class GtkDrawer: public BaseDrawer {
    Gtk::DrawingArea &_drawingArea;
    void _createLine(const Point2d &p1, const Point2d &p2);
public:
    explicit GtkDrawer(Gtk::DrawingArea &area): _drawingArea(area) {}
    virtual void draw(const shared_ptr<Component> scene, shared_ptr<BaseCamera> camera) override;
    virtual void clear() override;
};


void GtkDrawer::draw(shared_ptr<Component> obj, shared_ptr<BaseCamera> cam) {
    if (obj->isComposite()) // array of models and cams
        for (const auto &elem: scene)
            draw(elem);
    // ???????????????????????????????????????????????????//
    else if (obj->isVisible()) // model
    {
        // proection problems
        Point2d p1{1, 1}, p2{20, 400};
        _createLine(p1, p2);
    }
}


void GtkDrawer::_createLine(const Point2d &p1, const Point2d &p2) {
    auto cr = _drawingArea.get_window()->create_cairo_context();
    cr->move_to(p1.getX(), p1.getY());
    cr->line_to(p2.getX(), p2.getY());
    cr->stroke(); // stroke_preserve
}


void GtkDrawer::clear() {
    auto cr = _drawingArea.get_window()->create_cairo_context();
    cr->set_source_rgb(1, 1, 1);
    cr->paint();
    cr->stroke();
}
