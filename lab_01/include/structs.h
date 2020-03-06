#ifndef _STRUCTS_H_
#define _STRUCTS_H_

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
    point_t *arr; // points[N][4] - array with points.
    unsigned int size; // number of points.
    point_t cp; // center point.
} parr_t;

typedef struct links_array
{
    link_t *arr; // links[lsize][2]; N - number of links.
    unsigned int size; // number of links.
} larr_t;

typedef struct figure
{
    parr_t points;
    larr_t links;
} figure_t;

typedef struct event
{
    char command;
    char code;
} event_t;

typedef struct double_array
{
    double *array;
    unsigned int size;
} darr_t;

#endif
