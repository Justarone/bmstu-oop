#include "../include/draw_function.h"


err_t draw_figure(Gtk::DrawingArea *da, const fpr_t &projection)
{
    if (projection.points.size <= 0 || projection.links.size <= 0 || !projection.links.arr || 
            !projection.points.arr || !da)
        return DATA_ERROR;

    Cairo::RefPtr<Cairo::Context> cr = da->get_window()->create_cairo_context();
    cr->set_source_rgb(0., 0., 0.);
    cr->paint();
    cr->set_source_rgb(1., .5, 1.);
    cr->set_line_width(2);

    for (unsigned int i = 0; i < projection.links.size; i++)
    {
        cr->move_to(projection.points.arr[projection.links.arr[i].l1].x,
                projection.points.arr[projection.links.arr[i].l1].y);
        cr->line_to(projection.points.arr[projection.links.arr[i].l2].x,
                projection.points.arr[projection.links.arr[i].l2].y);
    }
    cr->stroke();

    return OK;
}
