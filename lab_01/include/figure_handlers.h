#ifndef _FIGURE_HANDLERS_H_
#define _FIGURE_HANDLERS_H_

#include "constants.h"
#include "figure.h"

#include <cstdio>
#include <limits>
#include <cmath>

err_t move_figure(parr_t &points, const point_t &dp);
err_t scale_figure(parr_t &points, const double sp); // sf - scale factor.
err_t rotate_figure(parr_t &points, const point_t &ap);
err_t match_figure_project(fpr_t &figure_projection, const figure_t &main_figure);
err_t read_projection(pparr_t &prj_points, const parr_t &main_points);

#endif
