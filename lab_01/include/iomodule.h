#ifndef _IOMODULE_H_
#define _IOMODULE_H_

#include "../include/structs.h"
#include "../include/constants.h"
#include <cstdio>
#include <cstdlib>

err_t read_from_file(figure_t &figure, const char *const filename);
void destroy_parr(); // parr == points_array.

#endif
