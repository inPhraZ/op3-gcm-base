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

typedef struct _dlinfo {
    char        *url;
    // etc...
} dlinfo;

dlinfo      *dlinfo_init(const char *url);
void        dlinfo_free(dlinfo *dli);

#define   /*  __OP3_GCM_BASE_DOWNLOADER_H_  */
