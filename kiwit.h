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

#define     KEY_LEN     32
#define     IV_LEN      16
//#define     TAG_LEN     16

typedef struct _kiwit {
    char        *key;
    char        *iv;
//    char       *tag;
} KIWIT;

KIWIT *kiwit_new(const char *key, const char *iv);
//KIWIT *kiwit_new(const char *key, const char *iv, const char *tag);

int kiwit_set_key(KIWIT *kiwit, const char *key);

int kiwit_set_iv(KIWIT *kiwit, const char *iv);

//int kiwit_set_tag(KIWIT *kiwit, const char *tag);

KIWIT *kiwit_free(KIWIT  *kiwit);

#endif      /*  __OP3_GCM_KIWIT_H_  */
