#include "../include/draw_module.h"


Cairo::RefPtr<Cairo::Context> get_canvas(Gtk::DrawingArea *const da, const canvas_conf &conf)
{
    Cairo::RefPtr<Cairo::Context> cr = da->get_window()->create_cairo_context();
    cr->set_source_rgb(conf.screen_rgb[0], conf.screen_rgb[1], conf.screen_rgb[2]);
    cr->paint();
    cr->set_source_rgb(conf.line_rgb[0], conf.line_rgb[1], conf.line_rgb[2]);
    cr->set_line_width(conf.line_width);

    return cr;
}


void create_line(Cairo::RefPtr<Cairo::Context> &cr, const ppoint_t from, const ppoint_t to)
{
    cr->move_to(from.x, from.y);
    cr->line_to(to.x, to.y);
}


void refresh_canvas(Cairo::RefPtr<Cairo::Context> &canvas)
{
    canvas->stroke();
}

canvas_conf init_canvas_conf(const canvas_conf *const conf_to_copy)
{
    canvas_conf conf = {};
    if (conf_to_copy)
        conf = *conf_to_copy;
    else
    {
        for (int i = 0; i < RGB_NUM; i++)
        {
            conf.screen_rgb[i] = DEFAULT_SCREEN_RGB[i];
            conf.line_rgb[i] = DEFAULT_LINE_RGB[i];
        }
        conf.line_width = DEFAULT_LINE_WIDTH;
    }
    return conf;
}

