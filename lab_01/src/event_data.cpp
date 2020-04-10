#include "../include/event_data.h"

event_data_t init_data()
{
    event_data_t data;

    data.load_data = init_load_data();
    data.draw_data = init_draw_data();
    data.trans_data = init_trans_data();
    data.prj_data = init_prj_data();

    return data;
}


void add_load_data(event_data_t &event_data, const char *filename)
{
    load_data_t data = init_load_data(filename);
    event_data.load_data = data;
}


void add_draw_data(event_data_t &event_data, Gtk::DrawingArea * area)
{
    draw_data_t data = init_draw_data(area);
    event_data.draw_data = data;
}


void add_trans_data(event_data_t &event_data, const double value)
{
    trans_data_t data = init_trans_data(value);
    event_data.trans_data = data;
}


void add_prj_data(event_data_t &event_data, fpr_t * projection)
{
    prj_data_t data = init_prj_data(projection);
    event_data.prj_data = data;
}


load_data_t init_load_data(const char *filename)
{
    load_data_t data;
    data.filename = filename;
    return data;
}

draw_data_t init_draw_data(Gtk::DrawingArea *area, canvas_conf *const conf)
{
    draw_data_t data;
    data.area = area;
    data.conf = init_canvas_conf(conf);
    return data;
}

trans_data_t init_trans_data(const double value)
{
    trans_data_t data;
    data.value = value;
    return data;
}

prj_data_t init_prj_data(fpr_t *projection)
{
    prj_data_t data;
    data.projection = projection;
    return data;
}
