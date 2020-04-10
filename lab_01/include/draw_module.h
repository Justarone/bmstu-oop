#ifndef _DRAW_MODULE_
#define _DRAW_MODULE_

#include <gtkmm-3.0/gtkmm.h>
#include "constants.h"
#include "points.h"

#define RGB_NUM 3 // number of elements in rgb list (always 3)

const double DEFAULT_SCREEN_RGB[RGB_NUM] = { 0.1, 0.2, 0.3 };
const double DEFAULT_LINE_RGB[RGB_NUM] = { 0.9, 0.8, 0.7 };
const int DEFAULT_LINE_WIDTH = 2;

struct canvas_configuration_items
{
    double screen_rgb[RGB_NUM];
    double line_rgb[RGB_NUM];
    int line_width;
};

using canvas_conf = struct canvas_configuration_items;

Cairo::RefPtr<Cairo::Context> get_canvas(Gtk::DrawingArea *const da, const canvas_conf &conf);
void create_line(Cairo::RefPtr<Cairo::Context> &cr, const ppoint_t from, const ppoint_t to);
void refresh_canvas(Cairo::RefPtr<Cairo::Context> &canvas);
canvas_conf init_canvas_conf(const canvas_conf *const conf_to_copy = NULL);

#endif
