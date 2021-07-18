/*
 * =====================================================================================
 *
 *       Filename:  region.h
 *        Created:  07/18/2021 08:43:17 PM
 *         Author:  Farzin 
 *
 * =====================================================================================
 */

#ifndef     __OP3_GCM_BASE_REGION_H_
#define     __OP3_GCM_BASE_REGION_H_

#include "block.h"

#define     SZ_PER_BLOCK        (20 * 1024)

typedef struct _region {
    Block           **blocks;
    size_t          sz;
    unsigned int    num_blks;
} Region;

Region  *region_new(const size_t sz);

Region  *region_free(Region *reg);

#endif      /*  __OP3_GCM_BASE_REGION_H_ */
