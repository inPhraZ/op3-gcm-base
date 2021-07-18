/*
 * =====================================================================================
 *
 *       Filename:  kiwit.h
 *        Created:  07/18/2021 07:30:51 PM
 *         Author:  Farzin 
 *
 * =====================================================================================
 */

#ifndef     __OP3_GCM_BASE_KIWIT_H_
#define     __OP3_GCM_BASE_KIWIT_H_

#include <stdint.h>

#define     KEY_LEN     32
#define     IV_LEN      16
//#define     TAG_LEN     16

typedef struct _kiwit {
    uint8_t        *key;
    uint8_t        *iv;
//    uint8_t       *tag;
} KIWIT;

KIWIT *kiwit_new(const uint8_t *key, const uint8_t *iv);
//KIWIT *kiwit_new(const uint8_t *key, const uint8_t *iv, const uint8_t *tag);

int kiwit_set_key(KIWIT *kiwit, const uint8_t *key);

int kiwit_set_iv(KIWIT *kiwit, const uint8_t *iv);

//int kiwit_set_tag(KIWIT *kiwit, const uint8_t *tag);

KIWIT *kiwit_free(KIWIT  *kiwit);

#endif      /*  __OP3_GCM_KIWIT_H_  */
