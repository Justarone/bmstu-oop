#ifndef _IO_POINTS_H_
#define _IO_POINTS_H_

#include "constants.h"
#include "points_arr.h"

#include <cstdlib>
#include <cstdio>

err_t find_center(parr_t &points);
err_t allocate_points(parr_t &points);
err_t read_points(FILE *const f, parr_t &points_array);
void destroy_points(parr_t &points);
void destroy_ppoints(pparr_t &points);

#endif
