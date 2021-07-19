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
#include "kiwit.h"

dlinfo *dlinfo_new()
{
    dlinfo *dli;

    dli = (dlinfo *)malloc(sizeof(dlinfo));
    if (!dli)
        return NULL;

    memset(dli, 0, sizeof(dlinfo));

    return dli;
}

int dlinfo_set_url(dlinfo *dli, const char *url)
{
    size_t urlen;

    if (!dli || !url)
        return 1;

    free(dli->url);

    urlen = strlen(url);
    dli->url = (char *)malloc(urlen + 1);
    if (!dli->url)
        return 1;

    memset(dli->url, 0, urlen + 1);
    strncpy(dli->url, url, urlen);

    return 0;
}

int dlinfo_set_kiwit(dlinfo *dli, KIWIT *kiwit)
{
    if (!dli || !kiwit)
        return 1;
    
    kiwit_free(dli->kiwit);
    dli->kiwit = kiwit;

    return 0;
}

int dlinfo_set_region(dlinfo *dli, Region *reg)
{
    if (!dli || !reg)
        return 1;

    region_free(dli->reg);
    dli->reg = reg;

    return 0;
}

dlinfo *dlinfo_free(dlinfo *dli)
{
    if (!dli)
        return NULL;
    free(dli->url);
    kiwit_free(dli->kiwit);
    region_free(dli->reg);
    // etc...
    free(dli);

    return NULL;
}
