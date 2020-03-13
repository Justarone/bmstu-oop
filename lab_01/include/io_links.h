#ifndef _IO_LINKS_H_
#define _IO_LINKS_H_

#include "links.h"
#include "constants.h"

#include <cstdlib>
#include <cstdio>

err_t read_links(FILE *const f, larr_t &links_array, const unsigned int max_index);
void destroy_links(larr_t &links);

#endif
