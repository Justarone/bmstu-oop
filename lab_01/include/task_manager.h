#ifndef _TASK_MANAGER_H_
#define _TASK_MANAGER_H_

#include "app_codes.h"
#include "constants.h"
#include "io_figure.h"
#include "figure.h"
#include "command_handlers.h"
#include "draw_function.h"

struct load_data
{
    const char* filename;
};
using load_data_t = struct load_data;


struct draw_data
{
    Gtk::DrawingArea *area;
};
using draw_data_t = struct draw_data;


struct transform_data
{
    double *value;
};
using trans_data_t = struct transform_data;


struct projection_data
{
    fpr_t *projection;
};
using prj_data_t = projection_data;

struct event_data
{
    load_data_t load_data;
    draw_data_t draw_data;
    trans_data_t trans_data;
    prj_data_t prj_data;
};
using event_data_t = struct event_data;

// command = MOVE, ROTATE, SCALE, DRAW, LOAD_DATA and etc.
// code = MOVE_UP, MOVE_DOWN and etc. (not every command use code (by default code = 0)).
struct event
{
    char command;
    char code;
};
using event_t = struct event;

err_t task_manager(const event_t &event, event_data_t &data);
event_t init_event(const char command = 0, const char code = 0);
event_data_t init_data(const char *const filename=NULL, Gtk::DrawingArea *const area=NULL,
        double *const value=NULL, fpr_t *const projection=NULL);

#endif
