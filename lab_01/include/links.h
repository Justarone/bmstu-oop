#ifndef _LINKS_H_
#define _LINKS_H_

struct link
{
    unsigned int l1;
    unsigned int l2;
};
using link_t = struct link;

struct links_array
{
    link_t *arr;
    unsigned int size;
};
using larr_t = struct links_array;

#endif
