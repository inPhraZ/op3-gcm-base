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
#include <math.h>

#include "region.h"

static void region_free_blocks(Block **blocks, const int e)
{
    if (!blocks)
        return;

    for (int i = 0; i < e; ++i)
        block_free(blocks[i]);

    free(blocks);
}

static Block **region_allocate_blocks(
        const unsigned int num_blks,
        const size_t sz)
{
    Blokc **blokcs;
    blocks = malloc(sizeof(Block *) * num_blks);
    if (!blocks)
        return NULL;

    for (int i = 0; i < num_blks; ++i){
        blocks[i] = block_new(sz);
        if (!blocks[i]){
            region_free_blocks(blocks, i);
            return NULL;
        }
    }
    return blocks;
}

Region *region_new(const size_t sz)
{
    Region *reg;
    reg = (Region *)malloc(sizeof(Region));
    if (!reg)
        return NULL;

    reg->sz = sz;
    reg->num_blks = ceil((double)sz / SZ_PER_BLOCK);

    reg->blocks = region_allocate_blocks(reg->num_blks, sz);
    if (!reg->blocks){
        free(reg);
        return NULL;
    }
    return reg;
}

Region *region_free(Region *reg)
{
    if (!reg)
        return NULL;
    region_free_blocks(reg->blocks, reg->num_blks);
    free(reg);
    return NULL;
}
