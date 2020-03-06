#ifndef _COMPUTATION_H_
#define _COMPUTATION_H_

#include "structs.h"
#include "constants.h"
#include <cmath>

err_t move_figure(parr_t &points, const double dx, const double dy, const double dz);
err_t scale_figure(parr_t &points, const double sf); // sf - scale factor.
err_t rotate_figure(parr_t &points, const double ax, const double ay, const double az);

#endif
