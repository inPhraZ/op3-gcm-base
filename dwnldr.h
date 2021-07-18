/*
 * =====================================================================================
 *
 *       Filename:  dwnldr.h
 *        Created:  07/18/2021 05:38:33 PM
 *         Author:  Farzin 
 *
 * =====================================================================================
 */

#ifndef   __OP3_GCM_BASE_DOWNLOADER_H_
#define   __OP3_GCM_BASE_DOWNLOADER_H_

#include "kiwit.h"
#include "region.h"

typedef struct _dlinfo {
    char        *url;
    KIWIT       *kiwit;
    Region      *reg;
    // etc...
} dlinfo;

dlinfo  *dlinfo_new();

int     dlinfo_set_url(dlinfo *dli, const char *url);

int     dlinfo_set_kiwit(dlinfo *dli, const KIWIT *kiwit);

int     dlinfo_set_region(dlinfo *dli, const Region *reg);

void    dlinfo_free(dlinfo *dli);

#define   /*  __OP3_GCM_BASE_DOWNLOADER_H_  */
