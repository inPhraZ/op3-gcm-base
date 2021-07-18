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

    if (!url)
        return NULL;
    
    dli = (dlinfo *)malloc(sizeof(dlinfo));
    if (!dl)
        return NULL;

    if (dlinfo_set_url(dli, url))
        return dlinfo_free(dli);

    return dli;
}

int dlinfo_set_url(dlinfo *dli, const char *url)
{
    size_t urlen;

    if (!dli || !url)
        return 1;

    // free prev url (if exists)
    if (dli->url)
        free(dli->url);

    urlen = strlen(url);
    dli->url = (char *)malloc(urlen + 1);
    if (!dli->url)
        return 1;

    memset(dli->url, 0, urlen + 1);
    strncpy(dli->url, url, urlen);

    return 0;
}

dlinfo *dlinfo_free(dlinfo *dli)
{
    if (!dli)
        return NULL;
    if (dli->url)
        free(dli->url);
    // etc...
    free(dli);

    return NULL;
}
