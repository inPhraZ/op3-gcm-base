/*
 * =====================================================================================
 *
 *       Filename:  kiwit.c
 *        Created:  07/18/2021 07:36:09 PM
 *         Author:  Farzin 
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <string.h>

#include "kiwit.h"

KIWIT *kiwit_new(const char *key, const char *iv)
{
    KIWIT *kiwit;

    if (!key || !iv)    return NULL;

    kiwit = (KIWIT *)malloc(sizeof(KIWIT));
    if (!kiwit)
        return NULL;

    kiwit->key = NULL;
    kiwit->iv = NULL;

    if (kiwit_set_key(kiwit, key))
        return kiwit_free(kiwit);

    if (kiwit_set_iv(kiwit, iv))
        return kiwit_free(kiwit);

    return kiwit;
}

int kiwit_set_key(KIWIT *kiwit, const char *key)
{
    if (!kiwit || !key)
        return 1;

    kiwit->key = (char *)malloc(KEY_LEN + 1);
    if (!kiwit->key)
        return 1;

    memset(kiwit->key, 0, KEY_LEN + 1);
    strncpy(kiwit->key, key, KEY_LEN);

    return 0;
}

int kiwit_set_iv(KIWIT *kiwit, const char *iv)
{
    if (!kiwit || !iv)
        return 1;

    kiwit->iv = (char *)malloc(IV_LEN + 1);
    if (!kiwit->iv)
        return 1;

    memset(kiwit->iv, 0, IV_LEN + 1);
    strncpy(kiwit->iv, iv, IV_LEN);

    return 0;
}

KIWIT *kiwit_free(KIWIT   *kiwit)
{
    if (!kiwit)
        return NULL;

    if (kiwit->key)
        free(kiwit->key);
    if (kiwit->iv)
        free(kiwit->iv);
    free(kiwit);

    return NULL;
}
