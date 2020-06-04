#include "drawer.hpp"

void GtkDrawer::drawLine(const Point2d &p1, const Point2d &p2) {
    _cr->move_to(p1.getX(), p1.getY());
    _cr->line_to(p2.getX(), p2.getY());
    _cr->stroke(); // stroke_preserve
    std::cout << "Point: " << p1.getX() << "; " << p1.getY() << " and " << 
        p2.getX() << "; " << p2.getY() << std::endl;
}


void GtkDrawer::clear() {
    _cr->set_source_rgb(1, 1, 1);
    _cr->paint();
    _cr->stroke();
    _cr->set_source_rgb(0, 0, 0);
}

GtkDrawer::GtkDrawer(const Cairo::RefPtr<Cairo::Context> &cr): _cr(cr) {}
