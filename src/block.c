/*
 * =====================================================================================
 *
 *       Filename:  block.c
 *        Created:  07/18/2021 08:38:12 PM
 *         Author:  Farzin 
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

#include "block.h"

Block *block_new(const size_t sz)
{
    Block *blk;
    blk = (Block *)malloc(sizeof(Block));
    if (!blk)
        return NULL;

    void *ptr = mmap(0, sz, PROT_READ | PROT_WRITE,
            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED){
        free(blk);
        return NULL;
    }

    blk->sptr = ptr;
    blk->wptr = ptr;
    blk->rptr = ptr;
    blk->woff = 0;
    blk->roff = 0;
    blk->sz = sz;
    blk->dlflag = 0;

    return blk;
}

Block *block_free(Block *blk)
{
    if (!blk)
        return NULL;

    munmap(blk->sptr, blk->sz);
    free(blk);
    return NULL;
}

ssize_t block_write(Block *blk, const void *buf, size_t count)
{
    if (!blk || !buf)
        return -1;

    size_t rem = (blk->sz - blk->woff);
    size_t sz = (rem >= count) ? count  : rem;

    memmove(blk->wptr, buf, sz);
    blk->wptr += sz;
    blk->woff += sz;

    return sz;
}

ssize_t block_read(Block *blk, void *buf, size_t count)
{
    if (!blk || !buf)
        return -1;

    size_t rem = (blk->sz - blk->roff);
    size_t sz = (rem >= count) ? count : rem;

    memmove(buf, blk->rptr, sz);
    blk->rptr += sz;
    blk->roff += sz;

    return sz;
}
