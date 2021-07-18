/*
 * =====================================================================================
 *
 *       Filename:  dwnldr.c
 *       Created:  07/18/2021 05:38:33 PM
 *         Author:  Farzin 
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <string.h>

#include "dwnldr.h"

dlinfo *dlinfo_init(const char *url)
{
    dlinfo *dli;
    size_t urlen;

    if (!url)   return NULL;
    
    dli = (dlinfo *)malloc(sizeof(dlinfo));
    if (!dl)    return NULL;

    urlen = strlen(url);
    dli->url = (char *)malloc(urlen + 1);
    if (!dli->url){
        free(dl);
        return NULL;
    }

    memset(dli->url, 0, urlen + 1);
    strncpy(dli->url, url, urlen);

    return dli;
}

void dlinfo_free(dlinfo *dli)
{
    if (!dli)    return;
    if (dli->url)
        free(dli->url);
    // etc...
    free(dli);
}
