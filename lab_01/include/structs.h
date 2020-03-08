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

typedef struct event_data
{
    Gtk::DrawingArea *area;
    double *value;
} event_data_t;

// command = MOVE, ROTATE, SCALE, DRAW, LOAD_DATA and etc.
// code = MOVE_UP, MOVE_DOWN and etc. (not every command use code (by default code = 0)).
typedef struct event
{
    char command;
    char code;
    event_data_t data;
} event_t;

#endif
