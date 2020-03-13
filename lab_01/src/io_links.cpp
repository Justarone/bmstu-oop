#include "../include/io_links.h"

static err_t allocate_link(larr_t &links_array)
{
    link_t *tmp = static_cast<link_t *>(realloc(links_array.arr,
            sizeof(link_t) * (links_array.size + 1)));
    if (!tmp)
        return ALLOCATION_ERROR;
    links_array.arr = tmp;

    return OK;
}


static err_t add_link(larr_t &links_array, const unsigned int l1, const unsigned int l2)
{
    err_t rc = allocate_link(links_array);
    if (!rc)
        return rc;
    links_array.arr[links_array.size].l1 = l1;
    links_array.arr[links_array.size].l2 = l2;
    
    links_array.size++;
    return OK;
}


err_t read_links(FILE *const f, larr_t &links_array, const unsigned int max_index)
{
    unsigned int l1, l2;
    while (fscanf(f, "%u%u", &l1, &l2) == 2 * READED) 
    {
        if (l1 > max_index || l2 > max_index)
            return DATA_ERROR;
        if (add_link(links_array, l1, l2))
            return ALLOCATION_ERROR;
    }
    return OK;
}


void destroy_links(larr_t &links)
{
    if (links.arr != NULL)
    {
        free(links.arr);
        links.arr = NULL;
    }
}
