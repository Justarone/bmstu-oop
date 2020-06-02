#include "drawer.hpp"

void GtkDrawer::drawLine(const Point2d &p1, const Point2d &p2) {
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

GtkDrawer::GtkDrawer(Gtk::DrawingArea &area): _drawingArea(area) {}
