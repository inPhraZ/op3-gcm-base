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

typedef struct _region {
    void    *sptr;
    void    *wptr;
    size_t  woff;
    size_t  sz;
} Region;

Region  *region_new(const size_t sz);

ssize_t region_append(Region *reg, const void *buf, size_t count);

Region  *region_free(Region *reg);

#endif      /*  __OP3_GCM_BASE_REGION_H_ */
