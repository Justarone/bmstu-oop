#include "../include/draw_function.h"


err_t draw_figure(Gtk::DrawingArea *da, const figure_t &figure)
{
    if (figure.points.size <= 0 || figure.links.size <= 0 || !figure.links.arr || 
            !figure.points.arr || !da)
        return DATA_ERROR;

    Cairo::RefPtr<Cairo::Context> cr = da->get_window()->create_cairo_context();
    cr->set_source_rgb(0., 0., 0.);
    cr->paint();
    cr->set_source_rgb(1., .5, 1.);
    cr->set_line_width(2);

    for (unsigned int i = 0; i < figure.links.size; i++)
    {
        cr->move_to(figure.points.arr[figure.links.arr[i].l1].x,
                figure.points.arr[figure.links.arr[i].l1].y);
        cr->line_to(figure.points.arr[figure.links.arr[i].l2].x,
                figure.points.arr[figure.links.arr[i].l2].y);
    }
    cr->stroke();

    return OK;
}
