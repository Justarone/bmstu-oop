#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include <cstdlib>
#include <gtkmm.h>

typedef struct point
{
    double x;
    double y;
    double z;
    double w;
} point_t;

typedef struct link
{
    unsigned int l1;
    unsigned int l2;
} link_t;

typedef struct points_array
{
    point_t *arr;
    unsigned int size;
    point_t cp;
} parr_t;

typedef struct links_array
{
    link_t *arr;
    unsigned int size;
} larr_t;

typedef struct figure
{
    parr_t points;
    larr_t links;
} figure_t;

typedef struct projection_point
{
    double x, y;
} ppoint_t;

typedef struct projection_points_array
{
    ppoint_t *arr;
    unsigned int size;
} pparr_t;

typedef struct figure_projection
{
    pparr_t points;
    larr_t links;
} fpr_t;

typedef struct event_data
{
    Gtk::DrawingArea *area;
    double *value;
    fpr_t *projection;
} event_data_t;

// command = MOVE, ROTATE, SCALE, DRAW, LOAD_DATA and etc.
// code = MOVE_UP, MOVE_DOWN and etc. (not every command use code (by default code = 0)).
typedef struct event
{
    char command;
    char code;
    event_data_t data;
} event_t;

event_t init_event(const char command = 0, const char code = 0,
                   Gtk::DrawingArea *const area = NULL, double *const value = NULL,
                   fpr_t *const projection = NULL);
figure_t init_figure(point_t *const parr = NULL, const unsigned int psize = 0,
        link_t *const larr = NULL, const unsigned int lsize = 0);
point_t init_point(const double x = 0, const double y = 0, const double z = 0, const double w = 1);
ppoint_t init_proj_point(const double x = 0, const double y = 0);
fpr_t init_projection(ppoint_t *const parr = NULL, const unsigned int psize = 0,
        link_t *const larr = NULL, const unsigned int lsize = 0);

#endif
