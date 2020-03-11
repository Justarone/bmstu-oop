#ifndef _TASK_MANAGER_H_
#define _TASK_MANAGER_H_

#include "app_codes.h"
#include "constants.h"
#include "iomodule.h"
#include "points_structs.h"
#include "command_handlers.h"
#include "draw_function.h"

struct event_data
{
    Gtk::DrawingArea *area;
    double *value;
    fpr_t *projection;
};
using event_data_t = struct event_data;

// command = MOVE, ROTATE, SCALE, DRAW, LOAD_DATA and etc.
// code = MOVE_UP, MOVE_DOWN and etc. (not every command use code (by default code = 0)).
struct event
{
    char command;
    char code;
    event_data_t data;
};
using event_t = struct event;

err_t task_manager(const event_t &event);
event_t init_event(const char command = 0, const char code = 0,
                   Gtk::DrawingArea *const area = NULL, double *const value = NULL,
                   fpr_t *const projection = NULL);

#endif
