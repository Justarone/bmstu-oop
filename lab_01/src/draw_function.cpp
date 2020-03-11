#include "../include/draw_function.h"


err_t draw_figure(Gtk::DrawingArea *da, const fpr_t &projection)
{
    pparr_t points = projection.points;
    larr_t links = projection.links;
    if (points.size <= 0 || links.size <= 0 || !links.arr || 
            !points.arr || !da)
        return DATA_ERROR;

    Cairo::RefPtr<Cairo::Context> cr = da->get_window()->create_cairo_context();
    cr->set_source_rgb(0., 0., 0.);
    cr->paint();
    cr->set_source_rgb(1., .5, 1.);
    cr->set_line_width(2);

    ppoint_t *points_array = points.arr;
    for (unsigned int i = 0; i < links.size; i++)
    {
        link_t cur_link = links.arr[i];
        cr->move_to(points_array[cur_link.l1].x,
                points_array[cur_link.l1].y);
        cr->line_to(points_array[cur_link.l2].x,
                points_array[cur_link.l2].y);
    }
    cr->stroke();

    return OK;
}
