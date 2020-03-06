#ifndef _STRUCTS_H_
#define _STRUCTS_H_

typedef struct points_array
{
    double **arr; // points[N][4] - array with points.
    unsigned int size; // number of points.
} parr_t;

typedef struct links_array
{
    unsigned int **arr; // links[lsize][2]; N - number of links.
    unsigned int size; // number of links.
} larr_t;

typedef struct figure
{
    parr_t points;
    larr_t links;
} figure_t;

#endif
