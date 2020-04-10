#include "../include/draw_function.h"


err_t draw_figure(Gtk::DrawingArea *const &da, const canvas_conf &conf, const fpr_t &projection)
{
    pparr_t points = projection.points;
    larr_t links = projection.links;

    if (points.size <= 0 || links.size <= 0 || !links.arr || !points.arr || !da)
        return DATA_ERROR;
    
    Cairo::RefPtr<Cairo::Context> canvas = get_canvas(da, conf);

    ppoint_t *points_array = points.arr;
    for (unsigned int i = 0; i < links.size; i++)
    {
        link_t cur_link = links.arr[i];
        create_line(canvas, points_array[cur_link.l1], points_array[cur_link.l2]);
    }
    refresh_canvas(canvas);

    return OK;
}
