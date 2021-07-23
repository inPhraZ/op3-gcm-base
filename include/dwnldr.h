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

typedef struct _dlinfo {
    char        *url;
    KIWIT       *kiwit;
    size_t      file_size;
    int         pipefds[2];
    // etc...
} dlinfo;

dlinfo  *dlinfo_new();

dlinfo  *dlinfo_free(dlinfo *dli);

int     dlinfo_set_url(dlinfo *dli, const char *url);

int     dlinfo_set_kiwit(dlinfo *dli, KIWIT *kiwit);

int     dlinfo_download(dlinfo *dli, 
                        pthread_t *doth,
                        pthread_t *deth);

#endif   /*  __OP3_GCM_BASE_DOWNLOADER_H_  */
