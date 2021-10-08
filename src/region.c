/*
 * =====================================================================================
 *
 *       Filename:  region.c
 *        Created:  07/18/2021 08:43:17 PM
 *         Author:  Farzin 
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#include "region.h"

Region *region_new(const size_t sz)
{
    Region *reg;
    reg = (Region *)malloc(sizeof(Region));
    if (!reg)
        return NULL;

    reg->sptr =
        mmap(NULL, sz, PROT_READ | PROT_WRITE,
             MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (reg->sptr == MAP_FAILED)
        return NULL;

    reg->wptr = reg->sptr;
    reg->rptr = reg->sptr;
    reg->woff = 0;
    reg->roff = 0;
    reg->sz = sz;

    return reg;
}

ssize_t region_append(Region *reg, const void *buf, size_t count)
{
    if (!reg)
        return -1;

    size_t sz = reg->sz - reg->woff;
    size_t numwr = (sz >= count) ? count : sz;
    memmove(reg->wptr, buf, numwr);
    reg->wptr += numwr;
    reg->woff += numwr;
    return numwr;
}

ssize_t region_read(Region *reg, void *buf, size_t count)
{
    if (!reg || !buf)
        return -1;

    size_t sz = reg->sz - reg->roff;
    size_t numrd = (sz >= count) ? count : sz;
    memmove(buf, reg->rptr, numrd);
    reg->rptr += numrd;
    reg->roff += numrd;
    return numrd;
}

Region *region_free(Region *reg)
{
    if (!reg)
        return NULL;
    free(reg);
    return NULL;
}
