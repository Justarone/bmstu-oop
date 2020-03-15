#ifndef _FIGURE_HANDLERS_H_
#define _FIGURE_HANDLERS_H_

#include "constants.h"
#include "figure.h"
#include "transform_point.h"

#include <cstdio>

err_t move_figure(parr_t &points, const point_t &dp);
err_t scale_figure(parr_t &points, const double sf); // sf - scale factor.
err_t rotate_figure(parr_t &points, const point_t &ap);

#endif
