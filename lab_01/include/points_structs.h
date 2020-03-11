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

struct points_array
{
    point_t *arr;
    unsigned int size;
    point_t cp;
};
using parr_t = struct points_array;

struct links_array
{
    link_t *arr;
    unsigned int size;
};
using larr_t = struct links_array;

struct figure
{
    parr_t points;
    larr_t links;
};
using figure_t = struct figure;

struct projection_point
{
    double x, y;
};
using ppoint_t = struct projection_point;

struct projection_points_array
{
    ppoint_t *arr;
    unsigned int size;
};
using pparr_t = struct projection_points_array;

struct figure_projection
{
    pparr_t points;
    larr_t links;
};
using fpr_t = struct figure_projection;

figure_t init_figure(point_t *const parr = NULL, const unsigned int psize = 0,
        link_t *const larr = NULL, const unsigned int lsize = 0);
point_t init_point(const double x = 0, const double y = 0, const double z = 0, const double w = 1);
ppoint_t init_proj_point(const double x = 0, const double y = 0);
fpr_t init_projection(ppoint_t *const parr = NULL, const unsigned int psize = 0,
        link_t *const larr = NULL, const unsigned int lsize = 0);

#endif
