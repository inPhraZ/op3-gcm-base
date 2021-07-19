/*
 * =====================================================================================
 *
 *       Filename:  block.h
 *        Created:  07/18/2021 08:38:12 PM
 *         Author:  Farzin 
 *
 * =====================================================================================
 */

#ifndef     __OP3_GCM_BASE_BLOCK_H_
#define     __OP3_GCM_BASE_BLOCK_H_

typedef struct _block {
    void        *sptr;
    void        *wptr;
    void        *rptr;
    size_t      woff;
    size_t      roff;
    size_t      sz;
    int         dlflag;
} Block;

Block   *block_new(const size_t sz);

Block   *block_free(Block *blk);

ssize_t  block_write(Block *blk, const void *buf, size_t count);

ssize_t  block_read(Block *blk, void *buf, size_t count);

#endif      /*  __OP3_GCM_BASE_BLOCK_H_ */
